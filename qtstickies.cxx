#include <QApplication>
#include <QTextEdit>

int main(int argc, char **argv)
{
 QApplication app (argc, argv);

 QWidget window;
 window.setFixedSize(300, 100);

 QTextEdit *text_edit = new QTextEdit(NULL, &window);

 window.setWindowFlags(Qt::WindowStaysOnTopHint);
 window.show();
 return app.exec();
}
