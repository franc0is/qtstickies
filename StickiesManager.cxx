#include "StickiesManager.h"

#include <QApplication>
#include <QDebug>
#include <QTGlobal>
#include <QDir>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QAction>
#include <QMenu>

#define STICKIES_DB_NAME "stickies.sqlite"
#define STICKIES_TABLE_NAME "stickies"

StickiesManager::StickiesManager() : QObject() {
  // Permanent data
  m_db = QSqlDatabase::addDatabase("QSQLITE");
  // FIXME might not be right place to put a DB for windows or ubuntu
  m_db.setDatabaseName(qApp->applicationDirPath()
                    + QDir::separator()
                    + "stickies.sqlite");

  if (!m_db.open()) {
    QMessageBox::critical(0, "DB Error", m_db.lastError().databaseText());
  } else if (!m_db.tables().contains(QLatin1String(STICKIES_TABLE_NAME))) {
    QSqlQuery("CREATE TABLE " STICKIES_TABLE_NAME
              "( id INTEGER PRIMARY KEY, "
              "color TEXT, "
              "width INTEGER, "
              "height INTEGER, "
              "text TEXT )",
              m_db);
  }
}

StickyWindow *StickiesManager::restoreStickies() {
   QSqlQuery query("SELECT * FROM " STICKIES_TABLE_NAME, m_db);
   const int textField = query.record().indexOf("text");
   const int idField = query.record().indexOf("id");
   const int colorField = query.record().indexOf("color");
   StickyWindow *curSticky = NULL;
   while (query.next()) {
     curSticky = new StickyWindow(0,
                                  query.value(idField).toInt(),
                                  query.value(textField).toString(),
                                  query.value(colorField).toString());
     connect(curSticky, SIGNAL (contentChanged(StickyWindow *)), this, SLOT (handleStickyChanged(StickyWindow *)));
     curSticky->show();
   }

   return curSticky;
}

StickyWindow *StickiesManager::newSticky() {
  // TODO probably should be a UUID so we don't have to worry about it
  int id = qrand();
  StickyWindow *sticky = new StickyWindow(0, id);
  connect(sticky, SIGNAL (contentChanged(StickyWindow *)), this, SLOT (handleStickyChanged(StickyWindow *)));
  sticky->show();
  return sticky;
}

StickyWindow *StickiesManager::currentSticky() {
  QWidget *focused = QApplication::focusWidget();
  // Not sure why that's required, but otherwise a child of StickyWindow is in focus
  while (focused->parentWidget()) {
    focused = focused->parentWidget();
  }

  StickyWindow *focusedSticky = qobject_cast<StickyWindow *>(focused);

  return focusedSticky;
}

// Slots
////////////////////////////////////////

void StickiesManager::handleNewSticky() {
  newSticky();
}

void StickiesManager::handleColorChanged(QAction *action) {
  StickyWindow *focusedSticky = currentSticky();
  if (!focusedSticky) {
    // no sticky is in focused, exit
    qDebug() << "Tried to change color when no sticky was in focus";
    return;
  }
  // First figure out the color
  focusedSticky->setColor(action->data().toString());
}

void StickiesManager::handleMenuWillShow() {
  QMenu *menu = qobject_cast<QMenu *>(QObject::sender());
  Q_ASSERT_X(menu != NULL, __FILE__, "MenuWillShow called by something not a menu");
  StickyWindow *topmostSticky = currentSticky();
  foreach (QAction *a, menu->actions()) {
    a->setChecked(topmostSticky->getColor().compare(a->data().toString()) == 0);
  }
}

void StickiesManager::handleStickyChanged(StickyWindow *sticky) {
  QSqlQuery query(m_db);
  query.prepare("INSERT OR REPLACE INTO " STICKIES_TABLE_NAME " ( id, color, width, height, text ) "
                "VALUES ( :id, :color, :width, :height, :text ) ");
  query.bindValue(":id", sticky->getId());
  query.bindValue(":color", sticky->getColor());
  query.bindValue(":width", 0); // FIXME
  query.bindValue(":height", 0); // FIXME
  query.bindValue(":text", sticky->getText());
  if (!query.exec()) {
    qDebug() << "Failed to exec query because";
    qDebug() << query.lastError().databaseText();
    qDebug() << query.lastError().driverText();
  }
}


