#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("");
    ui->label_2->setText("");
    b_error=false;
    n_error=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::b_Binario()
{
    qDebug()<<"Base : binario";
    base = 2;
    limpiar_resultados();
    c_Decimal();
    c_Hexadecimal();
    mostrar_resultado();
}

void MainWindow::b_Binario_bit_signo()
{
    qDebug()<<"Base : binario con bit de signo";
    base = -2;
    limpiar_resultados();
    c_Decimal_signo();
    mostrar_resultado();
}

void MainWindow::b_Hexadecimal()
{
    qDebug()<<"Base : hexadecimal";
    base = 16;
    limpiar_resultados();
    c_Binario();
    c_Decimal();
    mostrar_resultado();
}

void MainWindow::b_Decimal()
{
    qDebug()<<"Base : decimal";
    base = 10;
    limpiar_resultados();
    c_Binario();
    c_Hexadecimal();
    mostrar_resultado();
}

void MainWindow::c_automatico(QString num)
{
    n_Input = num;
    analizador();
    if((ui->radioButton->isChecked())==true){
        b_Binario();
    }
    if((ui->radioButton_4->isChecked())==true){
        b_Binario_bit_signo();
    }
    if((ui->radioButton_3->isChecked())==true){
        b_Decimal();
    }
    if((ui->radioButton_2->isChecked())==true){
        b_Hexadecimal();
    }
}

void MainWindow::analizador()
{
    int longitud = n_Input.size();
    int digito;
    n_error = false;
    while(longitud>0){
        longitud--;
        digito = n_Input[longitud].unicode();
        if(digito<48){
            n_error = true;
            longitud = 0;
        }
        if(digito<65 && digito>57){
            n_error = true;
            longitud = 0;
        }
        if(digito<97 && digito>70){
            n_error = true;
            longitud = 0;
        }
        if(digito>102){
            n_error = true;
            longitud = 0;
        }
    }

    qDebug()<<"error : "<<n_error;
}

void MainWindow::c_Binario()
{
    qDebug()<<"\tb_salida : binario";

    if(base == 10){
        unsigned int num;
        num = n_Input.toInt();
        while(num>0){
            if((num%2)==1){
                n_binario= "1" + n_binario;
            }
            else{
                n_binario= "0" + n_binario;
            }
            num = num/2;
        }
    }

    if(base == 16){
        int longitud = n_Input.size();
        int digito;
        int contador = 0;
        while(longitud>0){
            digito = n_Input[longitud-1].unicode();
            if(digito<58){
                digito = digito - 48;
            }
            else{
                if(digito>96){
                    digito = digito - 87;
                }
                else{
                    digito = digito - 55;
                }
            }
            while(contador<4){
                if((digito%2)==1){
                    n_binario= "1" + n_binario;
                }
                else{
                    n_binario= "0" + n_binario;
                }
                digito = digito / 2;
                contador++;
            }
            contador = 0;
            longitud--;
        }
    }
}

void MainWindow::c_Decimal()
{
    qDebug()<<"\tb_salida : decimal";

    unsigned int numero = 0;
    int contador = 0;
    int longitud = n_Input.size();

    if(base == 2){
        while(longitud>0){
            longitud--;
            if(n_Input[longitud]=='1'){
                int p_mult = 1;
                if(contador>0){
                    for(int i=0;i<contador;i++){
                        p_mult = 2 * p_mult;
                    }
                }
                numero = p_mult + numero;
            }
            contador++;
        }
    }

    //falta b16 a b10

    n_decimal.setNum(numero);
}

void MainWindow::c_Decimal_signo()
{
    qDebug()<<"\tb_salida : decimal con signo";

    int numero = 0;
    int contador = 0;
    int longitud = n_Input.size();

    if(base == -2){
      if(longitud%2==0){
          while(longitud>1){
              longitud--;
              if(n_Input[longitud]=='1'){
                  int p_mult = 1;
                  if(contador>0){
                      for(int i=0;i<contador;i++){
                          p_mult = 2 * p_mult;
                      }
                  }
                  numero = p_mult + numero;
              }
              contador++;
          }
          if(n_Input[0]=='1'){
              numero = numero * (-1);
              qDebug()<<"numero negativo : "<<numero;
          }
          b_error = false;
      }
      else{
          b_error = true;
          ui->lineEdit_3->setText("Error. Ingrese una longitud multiplo de 2.");
      }
    }

    n_decimal.setNum(numero);
}

void MainWindow::c_Hexadecimal()
{
    qDebug()<<"\tb_salida : hexadecimal";
    int longitud = n_Input.size();
    int contador = 0;
    int digito;
    int p_mult=1;

    if(base == 2){
        while(longitud>0){
            digito = 0;
            while(contador < 4 && longitud > 0){
                if(n_Input[longitud-1]=='1'){
                    digito = digito + p_mult;
                }
                p_mult = p_mult * 2;
                longitud--;
                contador++;
            }
            if(digito<10){
                digito = digito + 48;
            }
            else{
                digito = digito +55;
            }
            n_hexadecimal.prepend(digito);
            p_mult = 1;
            contador = 0;
        }
    }
}

void MainWindow::mostrar_resultado()
{
    qDebug()<<"resultados mostrados";
    if(base == 2){
        ui->label->setText("Decimal");
        ui->lineEdit_2->setText(n_decimal);
        ui->label_2->setText("Hexadecimal");
        ui->lineEdit_3->setText(n_hexadecimal);
    }

    if(base == -2){
        ui->label->setText("Decimal");
        ui->lineEdit_2->setText(n_decimal);
        ui->label_2->setText("");
        if(b_error==true){}
        else{
            ui->lineEdit_3->setEnabled(false);
        }
    }

    if(base == 10){
        ui->label->setText("Binario");
        ui->lineEdit_2->setText(n_binario);
        //ui->label_2->setText("Hexadecimal");
        ui->lineEdit_3->setEnabled(false);
    }

    if(base == 16){
        ui->label->setText("Binario");
        ui->lineEdit_2->setText(n_binario);
        //ui->label_2->setText("Decimal");
        ui->lineEdit_3->setEnabled(false);
    }
    if(n_error == true){
        ui->lineEdit->setStyleSheet("background-color: rgb(255, 212, 201);border-style: outset;border-width: 1px;border-radius: 3px;border-color: rgb(116, 116, 116);");
        ui->lineEdit_2->setText("acaba de ingresar un caracter no valido.");
        ui->lineEdit_3->setText("acaba de ingresar un caracter no valido.");
    }
}

void MainWindow::limpiar_resultados()
{
    qDebug()<<"limpiando buffer";
    qDebug()<<"int_base : "<<base;
    n_binario.clear();
    n_decimal.clear();
    n_hexadecimal.clear();
    ui->label->setText("");
    ui->label_2->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_3->setEnabled(true);
    ui->lineEdit->setStyleSheet("");
}
