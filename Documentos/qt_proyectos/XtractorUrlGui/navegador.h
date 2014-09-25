#ifndef NAVEGADOR_H
#define NAVEGADOR_H

#include <QDialog>
#include <QUrl>

namespace Ui {
class Navegador;
}

class Navegador : public QDialog
{
    Q_OBJECT
    int cancelar_todo;

public:
    explicit Navegador(QWidget *parent = 0);
    ~Navegador();
    void cargarUrl(QString url);
    QString url();
    int isCancelarTodo(){return cancelar_todo;}

private slots:
    void setUrl(QUrl newUrl);
    void c_all();

private:
    Ui::Navegador *ui;
};

#endif // NAVEGADOR_H
