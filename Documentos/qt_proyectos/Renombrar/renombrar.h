#ifndef RENOMBRAR_H
#define RENOMBRAR_H

#include <QMainWindow>

namespace Ui {
class Renombrar;
}

class Renombrar : public QMainWindow
{
    Q_OBJECT

public:
    explicit Renombrar(QWidget *parent = 0);
    ~Renombrar();

private:
    Ui::Renombrar *ui;
};

#endif // RENOMBRAR_H
