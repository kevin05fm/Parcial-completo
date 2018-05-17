#ifndef PUBLICACIONES_H_INCLUDED
#define PUBLICACIONES_H_INCLUDED
typedef struct
{
    char texto[64];
    int idCliente;
    int numeroRubro;
    int estado;
    //------------
    int idPublicaciones;
    int isEmpty;
}Publicaciones;

#include "cliente.h"


int publicar_init(Publicaciones* array,int limite);
int publicar_mostrarActivos(Publicaciones* arrayP,int limiteP,Cliente* array,int limite);
int publicar_alta(Publicaciones* arrayC,int limite,
              Cliente* clientes, int lenClientes);
int publicar_baja(Publicaciones* array,int limite, int id);
int publicar_modificacion(Publicaciones* array,int limite, int id);
int buscarPorId(Publicaciones* array,int limite, int id);
int publicar_MostrarClienteConPublicacionesActivas(Publicaciones* arrayP,int limiteP,Cliente* array,int limite);
int publicar_ClienteConMasPublicacionesActivas(Publicaciones* arrayP,int limiteP,Cliente* array,int limite);
//int publicar_altaForzada(Publicaciones* arrayC,int limite,Cliente* clientes, int lenClientes,int idCliente,char* archivo,char* cuit,int dias);
//int publicar_mostrarDebug(Publicaciones* array,int limite);
#endif // PANTALLA_H_INCLUDED



