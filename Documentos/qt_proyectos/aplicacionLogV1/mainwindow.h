#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void leerStdOut();
    void leerStdOutA();
    void iniciarApp();

private:
    Ui::MainWindow *ui;
    QProcess *app;
};

#endif // MAINWINDOW_H
