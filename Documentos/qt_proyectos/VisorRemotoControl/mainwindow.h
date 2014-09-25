#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QUdpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QTcpSocket* cliente;
    QUdpSocket* inputData;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void writeData(QString data);

private slots:
    void resizeEvent(QResizeEvent *event);
    void conectar();
    void desconectar();
    void inputImagen();
};

#endif // MAINWINDOW_H
