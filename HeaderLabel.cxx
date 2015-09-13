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



