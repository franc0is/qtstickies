#include <QApplication>

#include "StickyWindow.h"

int main(int argc, char **argv)
{
  QApplication app (argc, argv);

  // Window
  StickyWindow *window = new StickyWindow();

  // Go, go, go
  window->show();
  return app.exec();
}
