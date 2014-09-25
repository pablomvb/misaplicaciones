#ifndef TASKBAR_H
#define TASKBAR_H

#include <QWidget>

namespace Ui {
class TaskBar;
}

class TaskBar : public QWidget
{
    Q_OBJECT
    QString estado_task_bar;

public:
    explicit TaskBar(QWidget *parent = 0);
    ~TaskBar();

private:
    Ui::TaskBar *ui;

private slots:
    void estado(QString app);
    void btnInicio_press();
    void btnCaptura_press();
    void btnDescargas_press();
    void btnEmpaquetado_press();
    void btnRenombrar_press();
    void cambiarEstado(QString app);

signals:
    void aplicacion(QString app);
};

#endif // TASKBAR_H
