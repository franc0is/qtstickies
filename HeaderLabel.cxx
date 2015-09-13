#include "HeaderLabel.h"

#include <QWidget>
#include <QString>

HeaderLabel::HeaderLabel(const QString& text, QWidget* parent) : QLabel(parent) {
  this->setText(text);
}

HeaderLabel::~HeaderLabel() {
}

void HeaderLabel::mouseDoubleClickEvent(QMouseEvent* event) {
  emit clicked();
  this->setText("Clicked!");
}

