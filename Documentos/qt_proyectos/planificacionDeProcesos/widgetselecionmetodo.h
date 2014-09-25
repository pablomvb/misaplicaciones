#ifndef WIDGETSELECIONMETODO_H
#define WIDGETSELECIONMETODO_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class widgetSelecionMetodo;
}

class widgetSelecionMetodo : public QDialog
{
    Q_OBJECT

public:
    explicit widgetSelecionMetodo(QWidget *parent = 0);
    ~widgetSelecionMetodo();

private:
    Ui::widgetSelecionMetodo *ui;

public slots:
    void selectMetodo();

signals:
    void getMetodo(QString metodo);
};

#endif // WIDGETSELECIONMETODO_H
