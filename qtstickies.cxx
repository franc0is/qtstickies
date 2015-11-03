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
  StickyWindow *topmostSticky = stickiesManager->restoreStickies();
  if (topmostSticky == NULL) {
    topmostSticky = stickiesManager->newSticky();
  }

  // File Menu
  QMenu *fileMenu = new QMenu("File");
  // File -> New Note
  QAction *newStickyAction = new QAction("New Note", fileMenu);
  newStickyAction->setShortcuts(QKeySequence::New);
  stickiesManager->connect(newStickyAction, SIGNAL(triggered()), stickiesManager, SLOT (handleNewSticky()));
  fileMenu->addAction(newStickyAction);

  // Color Menu
  QMenu *colorMenu = new QMenu("Color");
  colorMenu->connect(colorMenu, SIGNAL(aboutToShow()), stickiesManager, SLOT (handleMenuWillShow()));
  QActionGroup *colorGroup = new QActionGroup(colorMenu);
  colorGroup->setExclusive(true);
  colorGroup->connect(colorGroup, SIGNAL(triggered(QAction *)), stickiesManager, SLOT (handleColorChanged(QAction *)));

  // Color->Yellow
  QAction *yellowColorAction = new QAction("Yellow", colorGroup);
  yellowColorAction->setData("yellow");
  yellowColorAction->setCheckable(true);
  colorGroup->addAction(yellowColorAction);
  colorMenu->addAction(yellowColorAction);
  yellowColorAction->setChecked(topmostSticky->getColor().compare(yellowColorAction->data().toString()) == 0);
  // Color->Red
  QAction *redColorAction = new QAction("Red", colorGroup);
  redColorAction->setData("red");
  redColorAction->setCheckable(true);
  colorGroup->addAction(redColorAction);
  colorMenu->addAction(redColorAction);
  redColorAction->setChecked(topmostSticky->getColor().compare(redColorAction->data().toString()) == 0);
  // Color->Green
  QAction *greenColorAction = new QAction("Green", colorGroup);
  greenColorAction->setData("green");
  greenColorAction->setCheckable(true);
  colorGroup->addAction(greenColorAction);
  colorMenu->addAction(greenColorAction);
  greenColorAction->setChecked(topmostSticky->getColor().compare(greenColorAction->data().toString()) == 0);
  // Color->Blue
  QAction *blueColorAction = new QAction("Blue", colorGroup);
  blueColorAction->setData("blue");
  blueColorAction->setCheckable(true);
  colorGroup->addAction(blueColorAction);
  colorMenu->addAction(blueColorAction);
  blueColorAction->setChecked(topmostSticky->getColor().compare(blueColorAction->data().toString()) == 0);
  // Color->Purple
  QAction *purpleColorAction = new QAction("Purple", colorGroup);
  purpleColorAction->setData("purple");
  purpleColorAction->setCheckable(true);
  colorGroup->addAction(purpleColorAction);
  colorMenu->addAction(purpleColorAction);
  purpleColorAction->setChecked(topmostSticky->getColor().compare(purpleColorAction->data().toString()) == 0);
  // Color->Grey
  QAction *greyColorAction = new QAction("Grey", colorGroup);
  greyColorAction->setData("grey");
  greyColorAction->setCheckable(true);
  colorGroup->addAction(greyColorAction);
  colorMenu->addAction(greyColorAction);
  greyColorAction->setChecked(topmostSticky->getColor().compare(greyColorAction->data().toString()) == 0);

  // Menu Bar
  // FIXME this only really works on OSX & ubuntu UI-wise.
  QMenuBar *menu_bar = new QMenuBar(0);
  menu_bar->addAction(fileMenu->menuAction());
  menu_bar->addAction(colorMenu->menuAction());
  menu_bar->setVisible(true);

  return app.exec();
}
