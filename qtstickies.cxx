#include <QApplication>
#include <QFile>

#include "StickyWindow.h"

int main(int argc, char **argv)
{
  QApplication app (argc, argv);

  // Window
  StickyWindow *window = new StickyWindow();

  // Load an application style
  QFile styleFile(":/stylesheet.qss");
  styleFile.open(QFile::ReadOnly);

  // Apply the loaded stylesheet
  QString style(styleFile.readAll());
  app.setStyleSheet(style);

  // Go, go, go
  window->show();
  return app.exec();
}
