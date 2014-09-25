#include <QApplication>
#include "wvisor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    WVisor visor;
    visor.show();

    return app.exec();
}
