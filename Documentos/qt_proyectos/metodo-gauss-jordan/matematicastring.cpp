#include "matematicastring.h"
#include <QStringList>


matematicaString::matematicaString()
{
    this->precision = 3;
}

int matematicaString::getPrecision()
{
    return this->precision;
}

void matematicaString::setPrecision(int precision)
{
    this->precision = precision;
}

QString matematicaString::dividirEntero(QString dividendo, QString divisor, int retorno)
{
    QString cociente;
    QString modulo;
    QString buffer;

    int divisorNum = divisor.toInt();

    buffer.clear();

    while(dividendo.count() > 0){
        buffer.append(dividendo.at(0));
        dividendo.remove(0,1);

        if(buffer.toInt() >= divisorNum){
            cociente.append(QString().setNum(buffer.toInt()/divisorNum));
            modulo = QString().setNum(buffer.toInt()%divisorNum);
            buffer = modulo;
        }
        else{
            if(cociente.count()!=0){
                cociente.append("0");
            }
            modulo = buffer;
        }
    }

    if(retorno == MODULO){
        return modulo;
    }
    if(cociente.count()==0){
        cociente.setNum(0);
    }
    return cociente;
}

QString matematicaString::dividirFlotante(QString dividendo, QString divisor, int retorno)
{
    QString cociente;
    QString modulo;
    QString buffer;
    int contadorDividendo = 0;
    int contadorDividendo2 = 0;
    int contadorDivisor = 0;
    int contadorDivisor2 = 0;
    int newPosicion = 0;
    bool sDividendo = false;
    bool sDivisor = false;

    if(divisor.contains(".")==true){
        sDivisor = true;
        QStringList numReal;
        numReal = divisor.split(".");
        if(numReal.count()>1){
            contadorDivisor = numReal.value(1).count();
            contadorDivisor2 = numReal.value(0).count();
        }
    }

    if(dividendo.contains(".")==true){
        sDividendo = true;
        QStringList numReal;
        numReal = dividendo.split(".");
        if(numReal.count()>1){
            contadorDividendo = numReal.value(1).count();
            contadorDividendo2 = numReal.value(0).count();
        }
    }

    if(contadorDivisor == contadorDividendo){
         divisor.remove(".");
         dividendo.remove(".");
         newPosicion = 0;
    }
    else{
        if(contadorDivisor > contadorDividendo){
            dividendo.remove(".");
            newPosicion = contadorDivisor - contadorDividendo;
            for(int i=0;i<newPosicion;i++){
                dividendo.append("0");
            }
            newPosicion = 0;
        }
        else{
            if(contadorDivisor < contadorDividendo){
                divisor.remove(".");
                dividendo.remove(".");
                newPosicion = dividendo.count()-(contadorDividendo - contadorDivisor);
                dividendo.insert(newPosicion,".");
                newPosicion = 0;
            }
            else{
                if(cociente.count()!=0){
                    cociente.append("0");
                }
                modulo = buffer;
            }
        }
    }

    int divisorNum = divisor.toInt();

    while(dividendo.count()>0){
        buffer.append(dividendo.at(0));
        dividendo.remove(0,1);
        if(buffer.contains(".")==true){
            buffer.remove(".");
            if(cociente.count()==0){
                cociente.append("0");
            }
            cociente.append(".");
        }
        if(buffer.toInt()>=divisorNum){
            cociente.append(QString().setNum(buffer.toInt()/divisorNum));
            modulo = QString().setNum(buffer.toInt()%divisorNum);
            buffer = modulo;
        }
    }

        QStringList analisis;
        analisis = cociente.split(".");
        int bucle = 0;
        if(analisis.count()>1){
            bucle = this->precision - analisis.value(1).count();
        }
        else{
            bucle = this->precision;
        }

        bucle++;

        for(int i=0;i<bucle;i++){
            if(buffer.toInt()<divisorNum){
                buffer.append("0");
            }
            else{
                cociente.append(QString().setNum(buffer.toInt()/divisorNum));
                modulo = QString().setNum(buffer.toInt()/divisorNum);
                buffer = modulo;
            }
        }

        QString numA = cociente.at(cociente.count()-1);
        cociente.remove(cociente.count()-1,1);

        if(numA.toInt()>4){
            numA = cociente.at(cociente.count()-1);
            cociente.remove(cociente.count()-1,1);
            numA = QString().setNum(numA.toInt()+1);
            cociente.append(numA);
        }

    if(retorno == MODULO){
        return modulo;
    }
    return cociente;
}
