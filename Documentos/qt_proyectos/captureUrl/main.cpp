#include <QCoreApplication>
#include <interfazapp.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    InterfazApp w;
    w.start();

    return a.exec();
}
