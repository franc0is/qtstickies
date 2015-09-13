#include "StickyWindow.h"
#include <QMouseEvent>

#define HEADER_HEIGHT 12

StickyWindow::StickyWindow(QWidget *parent) : QWidget(parent) {
  setFixedSize(300, 100);
  setWindowFlags(Qt::WindowStaysOnTopHint | // Always on top
                 Qt::CustomizeWindowHint);  // Don't show window decorators

  m_layout = new QVBoxLayout(this);
  m_layout->setContentsMargins(0, 0, 0, 0);
  m_layout->setSpacing(0);

  m_header = new HeaderLabel("", this);
  m_header->setFixedHeight(HEADER_HEIGHT);
  m_layout->addWidget(m_header);

  m_textBox = new QTextEdit(NULL, this);
  m_textBox->setMaximumWidth(300);
  m_layout->addWidget(m_textBox);

  m_isCollapsed = false;

  connect(m_header, SIGNAL (doubleClicked()), this, SLOT (handleHeaderCollapse()));
  connect(m_header, SIGNAL (pressed(QMouseEvent *)), this, SLOT (handleHeaderPressed(QMouseEvent *)));
  connect(m_header, SIGNAL (moved(QMouseEvent *)), this, SLOT (handleHeaderMoved(QMouseEvent *)));
}

StickyWindow::~StickyWindow() {
}

void StickyWindow::handleHeaderCollapse() {
  if (m_isCollapsed) {
    setFixedSize(300, 100);
    m_textBox->show();
    m_header->setText("");
    m_isCollapsed = false;
  } else {
    setFixedHeight(HEADER_HEIGHT);
    m_header->setText(m_textBox->toPlainText());
    m_textBox->hide();
    m_isCollapsed = true;
  }
}

void StickyWindow::handleHeaderPressed(QMouseEvent *e) {
  m_dragPosition = e->globalPos() - frameGeometry().topLeft();
}

void StickyWindow::handleHeaderMoved(QMouseEvent *e) {
  move(e->globalPos() - m_dragPosition);
}

