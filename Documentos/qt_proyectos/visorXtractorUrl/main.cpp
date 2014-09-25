#include "server.h"
#include "gui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gui b;
    b.show();

    return a.exec();
}
