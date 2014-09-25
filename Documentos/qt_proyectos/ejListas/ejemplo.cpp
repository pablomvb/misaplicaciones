#include "ejemplo.h"
#include <iostream>

ejemplo::ejemplo()
{
    ConsolaIO = new IOStream();
    archivoNuevo = false;
}

void ejemplo::iniciar()
{
    ConsolaIO->writeLine("Listas Ordenadas\n");
    cargarArchivo();
    ConsolaIO->writeLine("");
    ConsolaIO->writeLine(QString().setNum(cabecera.nRegistros));
}

void ejemplo::cargarArchivo()
{
    cabecera.nRegistros = 0;
    cabecera.primerRegistro = 0;
    cabecera.ultimoRegistro = 0;
    archivo = fopen("listas_ejemplo","r");
    if(archivo==NULL){
        ConsolaIO->writeLine("El archivo no existe\nSe a creado un nuevo archivo");
        archivo = fopen("listas_ejemplo","a+");
        fwrite(&cabecera,sizeof(cabecera),1,archivo);
        archivoNuevo = true;
    } else {
        fclose(archivo);
        archivo = fopen("listas_ejemplo","a+");
        ConsolaIO->writeLine("Archivo cargado");
        fread(&cabecera,sizeof(cabecera),1,archivo);
    }
}
