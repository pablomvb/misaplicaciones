#include "xtractor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Xtractor w;
    w.show();

    return a.exec();
}
