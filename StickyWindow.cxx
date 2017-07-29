// Copyright (C) 2015-present Francois Baldassari
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
#include <QApplication>
#include <QDebug>

#define HEADER_HEIGHT 13

StickyWindow::StickyWindow(QWidget *parent, int id, QString text, QString color) : QWidget(parent) {
  setWindowFlags(Qt::WindowStaysOnTopHint | // Always on top
                 Qt::CustomizeWindowHint  | // Don't show window decorators
                 Qt::FramelessWindowHint);

  m_layout = new QVBoxLayout(this);
  m_layout->setContentsMargins(QMargins());
  m_layout->setSpacing(0);

  m_header = new HeaderLabel("", this);
  m_header->setFixedHeight(HEADER_HEIGHT);
  m_layout->addWidget(m_header);

  m_textBox = new QTextEdit(NULL, this);
  m_textBox->setPlainText(text);
  m_textBox->setFrameShape(QFrame::NoFrame);
  m_layout->addWidget(m_textBox);

  m_grip = new QSizeGrip(this);
  m_layout->addWidget(m_grip, 0, Qt::AlignRight);

  m_isCollapsed = false;
  m_id = id;
  setProperty("stickyColor", color);

  connect(m_header, SIGNAL (doubleClicked()), this, SLOT (handleHeaderCollapse()));
  connect(m_header, SIGNAL (pressed(QMouseEvent *)), this, SLOT (handleHeaderPressed(QMouseEvent *)));
  connect(m_header, SIGNAL (moved(QMouseEvent *)), this, SLOT (handleHeaderMoved(QMouseEvent *)));
  connect(m_textBox, SIGNAL (textChanged()), this, SLOT (handleTextChanged()));
}

StickyWindow::~StickyWindow() {
  // TODO cleanup
}

// Setters
/////////////////////////////////////

void StickyWindow::setColor(QString colorName) {
  setProperty("stickyColor", colorName);
  // ~hack to recompute stylesheet
  QString style = qApp->styleSheet();
  qApp->setStyleSheet("/**/");
  qApp->setStyleSheet(style);
  // Content changed signal so new color is saved in DB
  emit contentChanged(this);
}

// Getters
/////////////////////////////////////

QString StickyWindow::getText() {
  return m_textBox->toPlainText();
}

QSize StickyWindow::getExpandedSize() {
  return m_size;
}

QString StickyWindow::getColor() {
  return property("stickyColor").toString();
}

int StickyWindow::getId() {
  return m_id;
}

bool StickyWindow::isCollapsed() {
  return m_isCollapsed;
}

// Setters
/////////////////////////////////////

void StickyWindow::setCollapsed(bool collapsed) {
  if (collapsed != m_isCollapsed) {
    handleHeaderCollapse();
  }
}

// Events
/////////////////////////////////////

void StickyWindow::resizeEvent(QResizeEvent *event) {
  QWidget::resizeEvent(event);
  if (!m_isCollapsed) {
    m_size = size();
    emit contentChanged(this);
  }
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
    m_grip->show();
    m_isCollapsed = false;
    setFixedHeight(QWIDGETSIZE_MAX);
    resize(m_size);
  } else {
    m_header->setText(m_textBox->toPlainText().split('\n')[0]);
    m_textBox->hide();
    m_grip->hide();
    m_isCollapsed = true;
    setFixedHeight(HEADER_HEIGHT);
  }
  emit contentChanged(this);
}

void StickyWindow::handleHeaderPressed(QMouseEvent *e) {
  m_dragPosition = e->globalPos() - frameGeometry().topLeft();
}

void StickyWindow::handleHeaderMoved(QMouseEvent *e) {
  move(e->globalPos() - m_dragPosition);
  emit contentChanged(this);
}

