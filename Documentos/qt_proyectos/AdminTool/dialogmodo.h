#ifndef DIALOGMODO_H
#define DIALOGMODO_H

#include <QDialog>

namespace Ui {
class DialogModo;
}

class DialogModo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogModo(QWidget *parent = 0);
    ~DialogModo();
    int getModo();

private:
    Ui::DialogModo *ui;
};

#endif // DIALOGMODO_H
