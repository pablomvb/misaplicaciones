#ifndef DIALOGSELECTION_H
#define DIALOGSELECTION_H

#include <QDialog>

namespace Ui {
class DialogSelection;
}

class DialogSelection : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSelection(QWidget *parent = 0);
    ~DialogSelection();
    QStringList clave();

private:
    Ui::DialogSelection *ui;
};

#endif // DIALOGSELECTION_H
