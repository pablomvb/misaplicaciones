#include "camara.h"
#include <QApplication>
#include <QGuiApplication>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QBuffer>
#include <QDebug>

Camara::Camara(QObject *parent) :
    QObject(parent)
{
    display = QGuiApplication::primaryScreen();
    click = new QTimer(this);
    socketUdpStreamDisplay = new QTcpSocket;
    setFrames();
    connect(click,SIGNAL(timeout()),this,SLOT(stream()));
}

QPixmap* Camara::getScreen()
{
    //screenshot = QPixmap::grabWindow(QApplication::desktop()->winId());
    //screenshot = display->grabWindow(QApplication::desktop()->winId());
    screenshot = new QPixmap(display->grabWindow(QApplication::desktop()->winId()));
    return screenshot;
}

void Camara::setFrames(int f)
{
    framesXsegundo = f;
    click->setInterval(1000/framesXsegundo);
}

void Camara::iniciarCaptura(QHostAddress ipBroadcast, int port)
{
    ipDestino = ipBroadcast;
    portDestino = port;
    //socketUdpStreamDisplay->bind(ipDestino,portDestino);
    click->start();
}

void Camara::detenerCaptura()
{
    click->stop();
}

void Camara::setIpAndPort(QString ipBroadcast, int port)
{
    ipDestino = ipBroadcast;
    portDestino = port;
    //socketUdpStreamDisplay->bind(ipDestino,portDestino);
}

void Camara::capturarAndSend()
{
    screenshot = new QPixmap(display->grabWindow(QApplication::desktop()->winId()));
    emit sendFrame(screenshot);
}

void Camara::stream()
{
    QByteArray bufferSend;
    QBuffer frame(&bufferSend);
    screenshot->toImage().save(&frame,"JPG");
    //qDebug()<<bufferSend;
    //socketUdpStreamDisplay->writeDatagram(bufferSend,ipDestino,portDestino);
}

/*
 *
 *
 *
 * QByteArray frameByteArray;
    QBuffer buffer(&frameByteArray);
    frame.toImage().save(&buffer,"JPG");
    socketFlujoDisplay->write(frameByteArray);

    */


// info QScreen :: grabWindow
//      http://ubuntuforums.org/showthread.php?t=2187649

// codigo visor
    //  //ui->visor->setPixmap(screenshot.scaled(ui->visor->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
        //ui->visor->setPixmap(screenshot);

