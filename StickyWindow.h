#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include "HeaderLabel.h"

class StickyWindow : public QWidget {
Q_OBJECT
public:
  explicit StickyWindow(QWidget *parent = 0);
  ~StickyWindow();
private slots:
  void handleHeaderCollapse();
  void handleHeaderPressed(QMouseEvent *e);
  void handleHeaderMoved(QMouseEvent *e);
private:
  QVBoxLayout *m_layout;
  HeaderLabel *m_header;
  QTextEdit *m_textBox;
  QPoint m_dragPosition;
  bool m_isCollapsed;
};
