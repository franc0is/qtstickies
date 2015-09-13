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
  void handleHeaderClick();
private:
  QVBoxLayout *m_layout;
  HeaderLabel *m_header;
  QTextEdit *m_textBox;
};

