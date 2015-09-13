#include <QLabel>

class HeaderLabel : public QLabel {
Q_OBJECT
public:
  explicit HeaderLabel(const QString& text="", QWidget* parent=0);
  ~HeaderLabel();
signals:
  void doubleClicked();
  void pressed(QMouseEvent *e);
  void moved(QMouseEvent *e);
protected:
  void mouseDoubleClickEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
};
