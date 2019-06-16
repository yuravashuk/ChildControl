#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Load QT Style Sheet
    QFile file(":/QSS/QSS/AppStyle.qss");
    if (file.open(QFile::ReadOnly))
    {
       QString style = QLatin1String(file.readAll());
       a.setStyleSheet(style);
    }

    w.show();

    return a.exec();
}
