// Copyright (C) 2015 Francois Baldassari
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

#include <QApplication>
#include <QAction>
#include <QFile>
#include <QMenuBar>
#include <QMenu>

#include "StickiesManager.h"

int main(int argc, char **argv)
{
  QApplication app (argc, argv);

  // Load an application style
  QFile styleFile(":/stylesheet.qss");
  styleFile.open(QFile::ReadOnly);
  QString style(styleFile.readAll());
  app.setStyleSheet(style);

  StickiesManager *stickiesManager = new StickiesManager();
  if (stickiesManager->restoreStickies() == 0) {
    stickiesManager->newSticky();
  }

  // Menu Bar
  // FIXME this only really works on OSX & ubuntu UI-wise.
  QAction *newStickyAction = new QAction("New Note", 0);
  newStickyAction->setShortcuts(QKeySequence::New);
  stickiesManager->connect(newStickyAction, SIGNAL(triggered()), stickiesManager, SLOT (handleNewSticky()));

  QMenu *menu = new QMenu("File");
  menu->addAction(newStickyAction);

  QMenuBar *menu_bar = new QMenuBar(0);
  menu_bar->addAction(menu->menuAction());
  menu_bar->setVisible(true);

  return app.exec();
}
