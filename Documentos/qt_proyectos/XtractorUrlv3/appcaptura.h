#ifndef APPCAPTURA_H
#define APPCAPTURA_H

#include <QWidget>

namespace Ui {
class AppCaptura;
}

class AppCaptura : public QWidget
{
    Q_OBJECT

public:
    explicit AppCaptura(QWidget *parent = 0);
    ~AppCaptura();

private:
    Ui::AppCaptura *ui;
};

#endif // APPCAPTURA_H
