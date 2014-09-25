#include "termianlremotacliente.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TermianlRemotaCliente w;
    w.show();

    return a.exec();
}
