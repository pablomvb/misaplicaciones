#include "socket.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    socket server;

    return a.exec();
}
