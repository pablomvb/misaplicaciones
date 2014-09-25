#ifndef XTRACTORURLV2_H
#define XTRACTORURLV2_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QPixmap>
#include <QClipboard>
#include <QApplication>
#include "dialogselection.h"
#include <QWebView>
//#include "downmanager.h"
#include "donwloadmanager.h"
#include "navegador.h"
#include "editor.h"

namespace Ui {
class XtractorUrlV2;
}

class XtractorUrlV2 : public QMainWindow
{
    Q_OBJECT

    // variables de aplicacion

        QStringList listScripts;
        QStringList instrucciones;

        QStringList _SubItems_list;
        QList<QTreeWidgetItem* > _SubItems;
        QList<QTreeWidgetItem* > _SubItemUrls;
        int _SubItemUltimaPosicion;
        int _SubItemUrlsUltimaPosicion;

    // -----------------------

    bool isAbortar;
    QWebView* webpage;
    QClipboard* system;
    QColor bColor;
    DonwloadManager xdm;

public:
    explicit XtractorUrlV2(QWidget *parent = 0);
    ~XtractorUrlV2();

private:
    Ui::XtractorUrlV2 *ui;
    void loadHead();
    void cargarScripts();
    bool cargarInstruncciones(QString nombrescript);
    void debug(QString msj);
    QString xtractor(QStringList arg, QByteArray data);
    QStringList xtractorList(QStringList arg, QByteArray data);
    void limpiar();
    void controlbotones(bool s,int e);

private slots:
    void editarscripts();
    void iniciarAnalisis();
    void cancelar();
    void copytoclipboard();

    void selec_e();
    void selec_all();
    void selec_noall();

    void editar();

    void e_basic();

    void redireccion_manual();
    void redireccion_auto();
};

#endif // XTRACTORURLV2_H
