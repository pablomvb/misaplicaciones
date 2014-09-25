#include "controlmaestro.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControlMaestro w;
    w.show();

    return a.exec();
}
