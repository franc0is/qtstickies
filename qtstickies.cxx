#include <QApplication>
#include <QVBoxLayout>
#include <QTextEdit>

#include "HeaderLabel.h"

int main(int argc, char **argv)
{
  QApplication app (argc, argv);

  // Window
  QWidget window;
  window.setFixedSize(300, 100);
  window.setWindowFlags(Qt::WindowStaysOnTopHint); // Always on top
  window.setWindowFlags(Qt::CustomizeWindowHint); // Don't show window decorators

  // Layout
  QVBoxLayout *layout = new QVBoxLayout(&window);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);

  // Header
  HeaderLabel *header = new HeaderLabel("Waiting", NULL);
  layout->addWidget(header);

  // Text box
  QTextEdit *text_edit = new QTextEdit(NULL, NULL);
  text_edit->setMaximumWidth(300);
  layout->addWidget(text_edit);

  // Go, go, go
  window.show();
  return app.exec();
}
