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

#include "HeaderLabel.h"

#include <QWidget>
#include <QString>
#include <QMouseEvent>

HeaderLabel::HeaderLabel(const QString& text, QWidget* parent) : QLabel(parent) {
  this->setText(text);
}

HeaderLabel::~HeaderLabel() {
}

void HeaderLabel::mouseDoubleClickEvent(QMouseEvent* event) {
  emit doubleClicked();
  event->accept();
}

void HeaderLabel::mouseMoveEvent(QMouseEvent* event) {
  if (event->buttons() & Qt::LeftButton) {
    emit moved(event);
    event->accept();
  }
}

void HeaderLabel::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    event->accept();
    emit pressed(event);
  }
}



