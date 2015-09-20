#include "StickyWindow.h"
#include <QMouseEvent>
#include <QFile>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

#define HEADER_HEIGHT 13

StickyWindow::StickyWindow(QWidget *parent, int id, QString text) : QWidget(parent) {
  setWindowFlags(Qt::WindowStaysOnTopHint | // Always on top
                 Qt::CustomizeWindowHint);  // Don't show window decorators

  m_layout = new QVBoxLayout(this);
  m_layout->setContentsMargins(0, 0, 0, 0);
  m_layout->setSpacing(0);

  m_header = new HeaderLabel("", this);
  m_header->setFixedHeight(HEADER_HEIGHT);
  m_layout->addWidget(m_header);

  m_textBox = new QTextEdit(NULL, this);
  m_textBox->setPlainText(text);
  m_layout->addWidget(m_textBox);

  m_status = new QStatusBar(this);
  m_layout->addWidget(m_status);

  m_isCollapsed = false;
  m_id = id;

  connect(m_header, SIGNAL (doubleClicked()), this, SLOT (handleHeaderCollapse()));
  connect(m_header, SIGNAL (pressed(QMouseEvent *)), this, SLOT (handleHeaderPressed(QMouseEvent *)));
  connect(m_header, SIGNAL (moved(QMouseEvent *)), this, SLOT (handleHeaderMoved(QMouseEvent *)));
  connect(m_textBox, SIGNAL (textChanged()), this, SLOT (handleTextChanged()));
}

StickyWindow::~StickyWindow() {
}

void StickyWindow::handleTextChanged() {
  // FIXME we should probably save this less often
  QSqlQuery query;
  query.prepare("INSERT OR REPLACE INTO stickies ( id, color, width, height, text ) "
                "VALUES ( :id, :color, :width, :height, :text ) ");
  query.bindValue(":id", m_id);
  query.bindValue(":color", 0); // FIXME
  query.bindValue(":width", 0); // FIXME
  query.bindValue(":height", 0); // FIXME
  query.bindValue(":text", m_textBox->toPlainText());
  if (!query.exec()) {
    qDebug() << "Failed to exec query because";
    qDebug() << query.lastError().databaseText();
    qDebug() << query.lastError().driverText();
  }
}

void StickyWindow::handleHeaderCollapse() {
  if (m_isCollapsed) {
    m_header->setText("");
    m_textBox->show();
    m_status->show();
    m_isCollapsed = false;
    setFixedHeight(QWIDGETSIZE_MAX);
    resize(m_size);
  } else {
    m_size = size();
    m_header->setText(m_textBox->toPlainText().split('\n')[0]);
    m_textBox->hide();
    m_status->hide();
    m_isCollapsed = true;
    setFixedHeight(HEADER_HEIGHT);
  }
}

void StickyWindow::handleHeaderPressed(QMouseEvent *e) {
  m_dragPosition = e->globalPos() - frameGeometry().topLeft();
}

void StickyWindow::handleHeaderMoved(QMouseEvent *e) {
  move(e->globalPos() - m_dragPosition);
}

