#include <QApplication>
#include <QFile>
#include <QSqlDatabase>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDir>

#include "StickyWindow.h"

#define STICKIES_DB_NAME "stickies.sqlite"
#define STICKIES_TABLE_NAME "stickies"

int main(int argc, char **argv)
{
  QApplication app (argc, argv);

  // Menu Bar
  // FIXME this only really works on OSX & ubuntu UI-wise.
  QMenu *menu = new QMenu("File");
  menu->addAction("bar1");
  menu->addAction("baz1");
  QMenuBar *menu_bar = new QMenuBar(0);
  menu_bar->addAction(menu->menuAction());
  menu_bar->setVisible(true);

  // Load an application style
  QFile styleFile(":/stylesheet.qss");
  styleFile.open(QFile::ReadOnly);
  QString style(styleFile.readAll());
  app.setStyleSheet(style);

  // Permanent data
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  // FIXME might not be right place to put a DB for windows or ubuntu
  db.setDatabaseName(qApp->applicationDirPath()
                    + QDir::separator()
                    + "stickies.sqlite");

  if (!db.open()) {
    QMessageBox::critical(0, "DB Error", db.lastError().databaseText());
    return -1;
  }

  if (!db.tables().contains(QLatin1String(STICKIES_TABLE_NAME))) {
    QSqlQuery("CREATE TABLE " STICKIES_TABLE_NAME
              "( id INTEGER PRIMARY KEY, "
              "color INTEGER, "
              "width INTEGER, "
              "height INTEGER, "
              "text TEXT )",
              db);
  }

   QSqlQuery query("SELECT * FROM " STICKIES_TABLE_NAME);
   const int textField = query.record().indexOf("text");
   const int idField = query.record().indexOf("id");
   bool anyWindow = false;
   while (query.next()) {
     StickyWindow *window = new StickyWindow(0,
                                             query.value(idField).toInt(),
                                             query.value(textField).toString());
     window->show();
     anyWindow = true;
   }

  // Window
  if (!anyWindow) {
    StickyWindow *window = new StickyWindow();
    window->show();
  }

  return app.exec();
}
