#ifndef DNEWAPP_H
#define DNEWAPP_H

#include <QDialog>

namespace Ui {
class dNewApp;
}

class dNewApp : public QDialog
{
    Q_OBJECT

public:
    explicit dNewApp(QWidget *parent = 0);
    ~dNewApp();

public slots:
    void btnOk();
    void cleanData();
    void setData(QString nameApp, QString cmdApp, int time, bool persistencia);

private:
    Ui::dNewApp *ui;

signals:
    void getData(QString nameApp, QString cmdApp, int time, bool persistencia);
};

#endif // DNEWAPP_H
