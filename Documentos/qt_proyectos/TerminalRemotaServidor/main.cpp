#include <QCoreApplication>
#include "sesion.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Sesion usurarioRemoto;
    usurarioRemoto.iniciarServicio();

    return a.exec();
}
