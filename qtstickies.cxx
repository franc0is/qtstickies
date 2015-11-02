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

  // File Menu
  QMenu *fileMenu = new QMenu("File");
  // File -> New Note
  QAction *newStickyAction = new QAction("New Note", 0);
  newStickyAction->setShortcuts(QKeySequence::New);
  stickiesManager->connect(newStickyAction, SIGNAL(triggered()), stickiesManager, SLOT (handleNewSticky()));
  fileMenu->addAction(newStickyAction);

  // Color Menu
  QMenu *colorMenu = new QMenu("Color", 0);
  // Color->Yellow
  QAction *yellowColorAction = new QAction("Yellow", 0);
  yellowColorAction->setData("yellow");
  stickiesManager->connect(yellowColorAction, SIGNAL(triggered()), stickiesManager, SLOT (handleColorChanged()));
  colorMenu->addAction(yellowColorAction);
  // Color->Red
  QAction *redColorAction = new QAction("Red", 0);
  redColorAction->setData("red");
  stickiesManager->connect(redColorAction, SIGNAL(triggered()), stickiesManager, SLOT (handleColorChanged()));
  colorMenu->addAction(redColorAction);
  // Color->Green
  QAction *greenColorAction = new QAction("Green", 0);
  greenColorAction->setData("green");
  stickiesManager->connect(greenColorAction, SIGNAL(triggered()), stickiesManager, SLOT (handleColorChanged()));
  colorMenu->addAction(greenColorAction);
  // Color->Blue
  QAction *blueColorAction = new QAction("Blue", 0);
  blueColorAction->setData("blue");
  stickiesManager->connect(blueColorAction, SIGNAL(triggered()), stickiesManager, SLOT (handleColorChanged()));
  colorMenu->addAction(blueColorAction);
  // Color->Purple
  QAction *purpleColorAction = new QAction("Purple", 0);
  purpleColorAction->setData("purple");
  stickiesManager->connect(purpleColorAction, SIGNAL(triggered()), stickiesManager, SLOT (handleColorChanged()));
  colorMenu->addAction(purpleColorAction);
  // Color->Grey
  QAction *greyColorAction = new QAction("Grey", 0);
  greyColorAction->setData("grey");
  stickiesManager->connect(greyColorAction, SIGNAL(triggered()), stickiesManager, SLOT (handleColorChanged()));
  colorMenu->addAction(greyColorAction);

  // Menu Bar
  // FIXME this only really works on OSX & ubuntu UI-wise.
  QMenuBar *menu_bar = new QMenuBar(0);
  menu_bar->addAction(fileMenu->menuAction());
  menu_bar->addAction(colorMenu->menuAction());
  menu_bar->setVisible(true);

  return app.exec();
}
