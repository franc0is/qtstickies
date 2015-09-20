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

