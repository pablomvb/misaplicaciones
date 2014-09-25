#include "renombrar.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Renombrar w;
    w.show();

    return a.exec();
}
