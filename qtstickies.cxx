#include <QApplication>
#include <QFile>
#include <QSqlDatabase>

#include "StickyWindow.h"

int main(int argc, char **argv)
{
  QApplication app (argc, argv);

  // Load an application style
  QFile styleFile(":/stylesheet.qss");
  styleFile.open(QFile::ReadOnly);
  QString style(styleFile.readAll());
  app.setStyleSheet(style);

  // Permanent data
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("stickies.db");

  // Window
  StickyWindow *window = new StickyWindow();

  // Go, go, go
  window->show();
  return app.exec();
}
