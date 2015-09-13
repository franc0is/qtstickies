#include "StickyWindow.h"
#include <QMouseEvent>

#define HEADER_HEIGHT 12

StickyWindow::StickyWindow(QWidget *parent) : QWidget(parent) {
  //setFixedSize(300, 100);
  setWindowFlags(Qt::WindowStaysOnTopHint); // Always on top
  setWindowFlags(Qt::CustomizeWindowHint); // Don't show window decorators

  m_layout = new QVBoxLayout(this);
  m_layout->setContentsMargins(0, 0, 0, 0);
  m_layout->setSpacing(0);

  m_header = new HeaderLabel("", this);
  m_header->setFixedHeight(HEADER_HEIGHT);
  m_layout->addWidget(m_header);

  m_textBox = new QTextEdit(NULL, this);
  m_textBox->setMaximumWidth(300);
  m_layout->addWidget(m_textBox);

  connect(m_header, SIGNAL (clicked()), this, SLOT (handleHeaderClick()));
}

StickyWindow::~StickyWindow() {
}

void StickyWindow::handleHeaderClick() {
  setFixedHeight(HEADER_HEIGHT);
  m_header->setText(m_textBox->toPlainText());
  m_textBox->hide();
}
