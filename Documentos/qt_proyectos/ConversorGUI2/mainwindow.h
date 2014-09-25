#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int base;
    bool b_error;
    bool n_error;
    QString n_binario;
    QString n_decimal;
    QString n_hexadecimal;
    QString n_Input;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void b_Binario();
    void b_Binario_bit_signo();
    void b_Hexadecimal();
    void b_Decimal();
    void c_automatico(QString num);
    void analizador();

private:
    void c_Binario();
    void c_Decimal();
    void c_Decimal_signo();
    void c_Hexadecimal();
    void mostrar_resultado();
    void limpiar_resultados();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
