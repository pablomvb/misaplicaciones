#include "sesionmana.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SesionMana w;
    w.show();

    return a.exec();
}
