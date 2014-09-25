#ifndef EJEMPLO_H
#define EJEMPLO_H

#include "iostream.h"
#include <cstdio>

struct head{
    int nRegistros;
    int ultimoRegistro;
    int primerRegistro;
};

class ejemplo
{
    IOStream* ConsolaIO;
    FILE* archivo;
    bool archivoNuevo;
    head cabecera;

public:
    ejemplo();
    void iniciar();
    void cargarArchivo();

};

#endif // EJEMPLO_H
