// Copyright (C) 2015-present Francois Baldassari
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

#include "StickiesManager.h"

#include <QApplication>
#include <QDebug>
#include <QTGlobal>
#include <QDir>
#include <QMessageBox>
#include <QStandardPaths>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QAction>
#include <QMenu>

#define STICKIES_DB_NAME "stickies.sqlite"
#define STICKIES_TABLE_NAME "stickies"

StickiesManager::StickiesManager() : QObject() {
  // DB for permanent data
  m_db = QSqlDatabase::addDatabase("QSQLITE");

  // Put it in appdata folder, create if it doesn't exist
  QString localDataPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  QDir dir(localDataPath);
  if (!dir.exists())
    dir.mkpath(localDataPath);
  m_db.setDatabaseName(localDataPath
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
              "posx INTEGER, "
              "posy INTEGER, "
              "isCollapsed INTEGER, "
              "text TEXT )",
              m_db);
  }
}

StickyWindow *StickiesManager::restoreStickies() {
  QSqlQuery query("SELECT * FROM " STICKIES_TABLE_NAME, m_db);
  const int textField = query.record().indexOf("text");
  const int idField = query.record().indexOf("id");
  const int colorField = query.record().indexOf("color");
  const int widthField = query.record().indexOf("width");
  const int heightField = query.record().indexOf("height");
  const int posXField = query.record().indexOf("posx");
  const int posYField = query.record().indexOf("posy");
  const int isCollapsedField = query.record().indexOf("isCollapsed");
  StickyWindow *curSticky = NULL;
  while (query.next()) {
    curSticky = new StickyWindow(0,
                                 query.value(idField).toInt(),
                                 query.value(textField).toString(),
                                 query.value(colorField).toString());
    connect(curSticky, SIGNAL (contentChanged(StickyWindow *)), this, SLOT (handleStickyChanged(StickyWindow *)));
    curSticky->setGeometry(query.value(posXField).toInt(),
                           query.value(posYField).toInt(),
                           query.value(widthField).toInt(),
                           query.value(heightField).toInt());
    curSticky->show();
    curSticky->setCollapsed((query.value(isCollapsedField).toInt() != 0));
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
  query.prepare("INSERT OR REPLACE INTO " STICKIES_TABLE_NAME " ( id, color, width, height, posx, posy, isCollapsed, text ) "
                "VALUES ( :id, :color, :width, :height, :posx, :posy, :isCollapsed, :text ) ");
  query.bindValue(":id", sticky->getId());
  query.bindValue(":color", sticky->getColor());
  query.bindValue(":width", sticky->getExpandedSize().width());
  query.bindValue(":height", sticky->getExpandedSize().height());
  query.bindValue(":posx", sticky->geometry().x());
  query.bindValue(":posy", sticky->geometry().y());
  query.bindValue(":isCollapsed", sticky->isCollapsed());
  query.bindValue(":text", sticky->getText());
  if (!query.exec()) {
    qDebug() << "Failed to exec query because";
    qDebug() << query.lastError().databaseText();
    qDebug() << query.lastError().driverText();
  }
}


