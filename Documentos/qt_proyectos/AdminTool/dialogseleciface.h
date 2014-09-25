#ifndef DIALOGSELECIFACE_H
#define DIALOGSELECIFACE_H

#include <QDialog>

namespace Ui {
class DialogSelecIface;
}

class DialogSelecIface : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSelecIface(QWidget *parent = 0);
    ~DialogSelecIface();
    void setDataIface(QStringList data);
    QString getIfaceSelec();

private:
    Ui::DialogSelecIface *ui;
};

#endif // DIALOGSELECIFACE_H
