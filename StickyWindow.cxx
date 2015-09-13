#include "StickyWindow.h"

StickyWindow::StickyWindow(QWidget *parent) : QWidget(parent) {
  m_layout = new QVBoxLayout(this);
  m_layout->setContentsMargins(0, 0, 0, 0);
  m_layout->setSpacing(0);

  m_header = new HeaderLabel("", this);
  m_layout->addWidget(m_header);

  m_textBox = new QTextEdit(NULL, this);
  m_textBox->setMaximumWidth(300);
  m_layout->addWidget(m_textBox);

  this->setFixedSize(300, 100);
  this->setWindowFlags(Qt::WindowStaysOnTopHint); // Always on top
  this->setWindowFlags(Qt::CustomizeWindowHint); // Don't show window decorators
}

StickyWindow::~StickyWindow() {
}

void StickyWindow::handleHeaderClick() {
}
