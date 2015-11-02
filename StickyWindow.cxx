// Copyright (C) 2015 Francois Baldassari
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>

#include "StickyWindow.h"
#include <QMouseEvent>
#include <QFile>

#define HEADER_HEIGHT 13

StickyWindow::StickyWindow(QWidget *parent, int id, QString text) : QWidget(parent) {
  setWindowFlags(Qt::WindowStaysOnTopHint | // Always on top
                 Qt::CustomizeWindowHint);  // Don't show window decorators

  setProperty("stickyColor", "yellow");

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
  // TODO cleanup
}

// Getters
/////////////////////////////////////

QString StickyWindow::getText() {
  return m_textBox->toPlainText();
}

QPoint StickyWindow::getPosition() {
  // TODO
  return QPoint(0, 0);
}

QSize StickyWindow::getExpandedSize() {
  // TODO
  return QSize(0, 0);
}

QColor StickyWindow::getColor() {
  // TODO
  return QColor(0, 0, 0);
}

int StickyWindow::getId() {
  return m_id;
}

// Slots
/////////////////////////////////////

void StickyWindow::handleTextChanged() {
  // FIXME we should probably emit this less often
  emit contentChanged(this);
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

