#include "sesion.h"

void Sesion::iniciarServidor()
{
    servidor =  new QTcpServer();
    if(servidor->listen(QHostAddress::LocalHost,6001)){
        qDebug()<<"Sevidor iniciado";
        connect(servidor,SIGNAL(newConnection()),this,SLOT(nuevoCliente()));
        qDebug()<<"Esperando cliente";
    }
    else{
        qDebug()<<"No se pudo iniciar el servidor";
    }
}

Sesion::Sesion(QObject *parent) :
    QObject(parent)
{
    aplicacion *bandejaNotificaciones = new aplicacion();
    bandejaNotificaciones->setObjectName("Bandeja de Notificaciones");
    listaAplicaciones<<bandejaNotificaciones;
    nuevaNotificacion("","Sesion Manager Daemon iniciado",IniciandoDaemon);
    loadListaAplicaciones();
    clienteConectado = false;
    iniciarServidor();
}

void Sesion::nuevoCliente()
{
    qDebug()<<"Nuevo Cliente";
    if(!clienteConectado){
        cliente = servidor->nextPendingConnection();
        connect(cliente,SIGNAL(readyRead()),this,SLOT(shell()));
        connect(cliente,SIGNAL(disconnected()),this,SLOT(desconectarCliente()));
        clienteConectado = true;
        qDebug()<<"Cliente conectado";
    }
    else{
        delete servidor->nextPendingConnection();
        qDebug()<<"Cliente rechazado";
    }
}

void Sesion::desconectarCliente()
{
    clienteConectado = false;
    qDebug()<<"Cliente desconectado";
}

void Sesion::writeDatos(QByteArray datos)
{
    cliente->write(datos);
    cliente->waitForBytesWritten(0);
}

void Sesion::shell()
{
    QStringList cmds = QString(cliente->readAll()).split("\n");
    qDebug()<<"Datos entrantes";
    //qDebug()<<cmds;

    int comando;

    for (int var = 0; var < cmds.count(); ++var) {
        if(cmds.value(var).count() > 0){
            QStringList cmd = cmds.value(var).split("|||");
            //qDebug()<<cmd;
            comando = cmd.value(0).toInt();
            cmd.removeFirst();
            switch (comando) {
            case -1:
                comando_actualizarCliente();
            break;
            case 1:
                comando_nuevaApliacion(cmd);
            break;
            }
        }
    }
}

void Sesion::nuevaNotificacion(QString apliacion, QString informacion, int estado)
{
    aplicacion* bandeja = listaAplicaciones.value(0);
    QStringList argNotificacion;

    argNotificacion<<"Control de Sesion";

    switch (estado) {
    case AplicacionInciada:
        argNotificacion<<apliacion+": iniciado";
        argNotificacion<<"--icon=media-playback-start-symbolic";
        break;
    case AplicacionTerminada:
        argNotificacion<<apliacion+": terminado";
        argNotificacion<<"--icon=media-playback-stop-symbolic";
        break;
    case AplicacionReset:
        argNotificacion<<apliacion+": reiniciado";
        argNotificacion<<"--icon=media-playlist-repeat-symbolic";
        break;
    case AplicacionError:
        argNotificacion<<apliacion+": tiene problemas";
        argNotificacion<<"--icon=bolt3";
        break;
    case IniciandoDaemon:
        argNotificacion<<informacion;
        argNotificacion<<"--icon=system-run-symbolic";
        break;
    case Apagar:
        argNotificacion<<"ApagandoS istema";
        argNotificacion<<"--icon=system-shutdown-symbolic";
        break;
    case Reiniciar:
        argNotificacion<<"Reiniciando Sistema";
        argNotificacion<<"--icon=view-refresh-symbolic";
        break;
    case Bloquear:
        argNotificacion<<"Bloqueando pantalla";
        argNotificacion<<"--icon=system-lock-screen";
        break;
    }

    bandeja->setAplicacionComando("notify-send",
                                                argNotificacion,
                                                false,
                                                0);
    bandeja->iniciar();
}

void Sesion::loadListaAplicaciones()
{
    QFile fileAplicaciones;
    qDebug()<<"Cargando lista de aplicaciones";
    fileAplicaciones.setFileName("/home/pablomvb/xAplicacion/controlSesion.conf");
    if(fileAplicaciones.open(QIODevice::ReadOnly)){
        QString data = fileAplicaciones.readAll();
        if(data.count()>0){
            QStringList listSubData = data.split("\n");
            qDebug()<<listSubData;
        }
        else{
            qDebug()<<"Sin datos";
        }
    }
    else{
        qDebug()<<"No se encontro las lista de aplicaciones";
    }
}

void Sesion::comando_nuevaApliacion(QStringList aplicacionCmdArg)
{
    qDebug()<<"Comando 1: "<<aplicacionCmdArg;
    bool persistencia = false;
    if(aplicacionCmdArg.value(3).contains("true")){
        persistencia = true;
    }
    aplicacion* aplicacionItem = new aplicacion();
    listaAplicaciones<<aplicacionItem;
    aplicacionItem->setObjectName(aplicacionCmdArg.value(0));
    aplicacionItem->setAplicacionComando(aplicacionCmdArg.value(1),
                                         aplicacionCmdArg.value(2).split(";;"),
                                         persistencia,
                                         aplicacionCmdArg.value(4).toInt());
    conectarAplicacionBandeja(aplicacionItem);
    if(!aplicacionCmdArg.value(5).contains("NOAPLICAR")){
        aplicacionItem->iniciar();
    }
    comando_actualizarCliente();
}

void Sesion::comando_actualizarCliente()
{
    QStringList listDatos;
    listDatos<<"0";
    for(int i=0; i<listaAplicaciones.count(); i++){
        listDatos<<listaAplicaciones.value(i)->getDatosAplicacion();
    }
    qDebug()<<listDatos;
    writeDatos(listDatos.join("\n").toLatin1());
}

void Sesion::conectarAplicacionBandeja(aplicacion *ptrAplicacion)
{
    connect(ptrAplicacion,SIGNAL(mensajeBandejaDeNotificacion(QString,QString,int)),this,SLOT(nuevaNotificacion(QString,QString,int)));
    connect(ptrAplicacion,SIGNAL(actualizar()),this,SLOT(comando_actualizarCliente()));
}

void Sesion::desconectarAplicacionBandeja(aplicacion *ptrAplicacion)
{
    disconnect(ptrAplicacion,SIGNAL(mensajeBandejaDeNotificacion(QString,QString,int)),this,SLOT(nuevaNotificacion(QString,QString,int)));
    disconnect(ptrAplicacion,SIGNAL(actualizar()),this,SLOT(comando_actualizarCliente()));
}
