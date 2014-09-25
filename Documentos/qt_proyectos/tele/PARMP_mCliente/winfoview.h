#ifndef WINFOVIEW_H
#define WINFOVIEW_H

#include <QWidget>

namespace Ui {
class wInfoView;
}

class wInfoView : public QWidget
{
    Q_OBJECT

public:
    explicit wInfoView(QWidget *parent = 0);
    ~wInfoView();

public slots:
    void setEstado(int estado);

private:
    Ui::wInfoView *ui;
};

#endif // WINFOVIEW_H
