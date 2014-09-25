#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString metodoSelecionado;
    int mSelecionado;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setMetodo(QString metodo);

private:
    Ui::MainWindow *ui;

signals:
    void getMetodo(int metodo);
private slots:
    void on_actionFCFS_triggered();
    void on_actionSJF_triggered();
    void on_actionBasado_en_prioridades_triggered();
    void on_actionRound_Robin_triggered();
    void on_actionMulticolas_triggered();
    void on_actionMultiprocesos_triggered();
};

#endif // MAINWINDOW_H
