#ifndef DIALOGVARCONFIG_H
#define DIALOGVARCONFIG_H

#include <QDialog>

namespace Ui {
class DialogVarConfig;
}

class DialogVarConfig : public QDialog
{
    Q_OBJECT
    QStringList datos;
    int estado;
    int index;

public:
    explicit DialogVarConfig(QWidget *parent = 0);
    ~DialogVarConfig();

private:
    Ui::DialogVarConfig *ui;
    void cargarDatos();
    void enableTxt(bool std);

private slots:
    void nuevoscript();
    void cambiarscript(int i);
    void guardar();
    void eliminar();
};

#endif // DIALOGVARCONFIG_H
