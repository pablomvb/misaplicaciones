#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include "server.h"

namespace Ui {
class Gui;
}

class Gui : public QWidget
{
    Q_OBJECT
    server* InputDataObject;

public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();

private:
    Ui::Gui *ui;

public slots:
    void setData(QString d);
    void clean();
    void CopyToClipBoard();

};

#endif // GUI_H
