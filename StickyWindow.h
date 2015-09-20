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

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QSizeGrip>
#include <QStatusBar>
#include "HeaderLabel.h"

class StickyWindow : public QWidget {
Q_OBJECT
public:
  explicit StickyWindow(QWidget *parent = 0, int id = 0, QString text = "");
  ~StickyWindow();
private slots:
  void handleHeaderCollapse();
  void handleHeaderPressed(QMouseEvent *e);
  void handleHeaderMoved(QMouseEvent *e);
  void handleTextChanged();
private:
  QVBoxLayout *m_layout;
  HeaderLabel *m_header;
  QTextEdit *m_textBox;
  QStatusBar *m_status;
  QPoint m_dragPosition;
  bool m_isCollapsed;
  QColor m_color;
  QSize m_size;
  int m_id;
};

