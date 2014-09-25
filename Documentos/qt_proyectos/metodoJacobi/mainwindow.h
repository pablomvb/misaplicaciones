#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QStringList>
#include <QString>
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int matriz_size;
    QStringList nameHeaderTbl;
    QStringList nameHeaderTblR;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void initTblR();
    void numerar();
    bool validarMatriz();
    void calcular(int rowF);
    QString calcularItem(int varX,int varY,float mulX);

private slots:
    void sizeTableMatriz(int size);
    void initJacobi();
};

#endif // MAINWINDOW_H
