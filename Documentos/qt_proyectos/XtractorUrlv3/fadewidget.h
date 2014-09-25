#ifndef FADEWIDGET_H
#define FADEWIDGET_H

#include <QWidget>

class QTimer;

class FadeWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor fadeColor READ fadeColor WRITE setFadeColor)
    Q_PROPERTY(int fadeDuration READ fadeDuration WRITE setFadeDuration)
public:
    explicit FadeWidget(QWidget *parent = 0);
    QColor fadeColor() const { return startColor; }
    void setFadeColor(const QColor &newColor) { startColor = newColor; }

    int fadeDuration() const { return duration; }
    void setFadeDuration(int milliseconds) { duration = milliseconds; }

    void start();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QTimer *timer;
    QColor startColor;
    int currentAlpha;
    int duration;

signals:

public slots:

};

#endif // FADEWIDGET_H
