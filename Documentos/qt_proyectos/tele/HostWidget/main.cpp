#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setModoLoad(0);
    w.setup();
    w.show();

    return a.exec();
}
