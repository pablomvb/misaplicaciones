#ifndef MATEMATICASTRING_H
#define MATEMATICASTRING_H

#include <QString>

#define ENTERO 1
#define FLOTANTE 2
#define COCIENTE 3
#define MODULO 4

class matematicaString
{
private:
    int precision;

public:
    matematicaString();
    int getPrecision();
    void setPrecision(int precision);
    QString dividirEntero(QString dividendo, QString divisor, int retorno);
    QString dividirFlotante(QString dividendo, QString divisor, int retorno);

};

#endif // MATEMATICASTRING_H
