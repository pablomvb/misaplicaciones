#ifndef XTRACTOR_H
#define XTRACTOR_H

#include <QMainWindow>

#include "fadewidget.h"
#include <QListWidgetItem>
#include <QPointer>

namespace Ui {
class Xtractor;
}

class Xtractor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Xtractor(QWidget *parent = 0);
    ~Xtractor();

private:
    Ui::Xtractor *ui;

    QPointer<FadeWidget> faderWidget;

private slots:
    void cambiarAplicacion(QString app);

    void fadeInWidget(int i);
};

#endif // XTRACTOR_H
