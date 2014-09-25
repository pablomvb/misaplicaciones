#include "pkgcbfile.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pkgCBFile w;
    w.show();

    return a.exec();
}
