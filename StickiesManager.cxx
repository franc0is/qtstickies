#include "StickiesManager.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QAction>

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
              "color INTEGER, "
              "width INTEGER, "
              "height INTEGER, "
              "text TEXT )",
              m_db);
  }
}

int StickiesManager::restoreStickies() {
   QSqlQuery query("SELECT * FROM " STICKIES_TABLE_NAME, m_db);
   const int textField = query.record().indexOf("text");
   const int idField = query.record().indexOf("id");
   int numStickies = 0;
   while (query.next()) {
     StickyWindow *sticky = new StickyWindow(0,
                                             query.value(idField).toInt(),
                                             query.value(textField).toString());
     connect(sticky, SIGNAL (contentChanged(StickyWindow *)), this, SLOT (handleStickyChanged(StickyWindow *)));
     sticky->show();
     numStickies++;
   }

   return numStickies;
}

void StickiesManager::newSticky() {
  StickyWindow *sticky = new StickyWindow(0, rand(), "");
  connect(sticky, SIGNAL (contentChanged(StickyWindow *)), this, SLOT (handleStickyChanged(StickyWindow *)));
  sticky->show();
}

// Slots
////////////////////////////////////////

void StickiesManager::handleNewSticky() {
  newSticky();
}

void StickiesManager::handleColorChanged() {
  QWidget *focused = QApplication::focusWidget();
  // Not sure why that's required, but otherwise a child of StickyWindow is in focus
  while (focused->parentWidget()) {
    focused = focused->parentWidget();
  }

  StickyWindow *focusedSticky = qobject_cast<StickyWindow *>(focused);
  if (!focusedSticky) {
    // no sticky is in focused, exit
    qDebug() << "Tried to change color when no sticky was in focus";
    return;
  }
  // First figure out the color
  QAction *triggeredAction = qobject_cast<QAction *>(QObject::sender());
  focusedSticky->setColor(triggeredAction->data().toString());
}

void StickiesManager::handleStickyChanged(StickyWindow *sticky) {
  QSqlQuery query(m_db);
  query.prepare("INSERT OR REPLACE INTO " STICKIES_TABLE_NAME " ( id, color, width, height, text ) "
                "VALUES ( :id, :color, :width, :height, :text ) ");
  query.bindValue(":id", sticky->getId());
  query.bindValue(":color", 0); // FIXME
  query.bindValue(":width", 0); // FIXME
  query.bindValue(":height", 0); // FIXME
  query.bindValue(":text", sticky->getText());
  if (!query.exec()) {
    qDebug() << "Failed to exec query because";
    qDebug() << query.lastError().databaseText();
    qDebug() << query.lastError().driverText();
  }
}


