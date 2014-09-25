#include <QCoreApplication>
#include "ejemplo.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ejemplo listas;
    listas.iniciar();

    return a.exec();
}
