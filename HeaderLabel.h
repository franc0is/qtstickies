#include <QLabel>

class HeaderLabel : public QLabel {
Q_OBJECT
public:
  explicit HeaderLabel(const QString& text="", QWidget* parent=0);
  ~HeaderLabel();
signals:
  void clicked();
protected:
  void mouseDoubleClickEvent(QMouseEvent* event);
};
