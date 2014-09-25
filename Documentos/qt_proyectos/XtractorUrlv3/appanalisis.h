#ifndef APPANALISIS_H
#define APPANALISIS_H

#include <QWidget>

namespace Ui {
class AppAnalisis;
}

class AppAnalisis : public QWidget
{
    Q_OBJECT

public:
    explicit AppAnalisis(QWidget *parent = 0);
    ~AppAnalisis();

private:
    Ui::AppAnalisis *ui;
};

#endif // APPANALISIS_H
