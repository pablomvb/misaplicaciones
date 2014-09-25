#include <QCoreApplication>
#include <xtractorurl.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    XtractorUrl app;
    app.start();

    return a.exec();
}
