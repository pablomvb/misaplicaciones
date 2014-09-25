#include "xtractorurlv2.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    XtractorUrlV2 w;
    w.setWindowTitle("XtractorUrl 2");
    w.show();

    return a.exec();
}
