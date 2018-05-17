#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "publicaciones.h"
#include "utn.h"
#include "cliente.h"



//Funciones privadas

static int proximoId(void);


static int buscarLugarLibre(Publicaciones* array,int limite);
//__________________



int publicar_init(Publicaciones* array,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            array[i].isEmpty=1;
        }
    }
    return retorno;
}

int publicar_mostrarDebug(Publicaciones* array,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            //printf("[DEBUG] - %d - %s - %s - %d - %d\n",array[i].id, array[i].cuit,array[i].archivo,array[i].dias, array[i].isEmpty);
        }
    }
    return retorno;
}

int publicar_mostrarActivos(Publicaciones* arrayP,int limiteP,Cliente* array,int limite)
{
    int retorno = -1;
    int i;


    if(limite > 0 && array != NULL)
    {
        retorno = 0;

        printf("ID  -  RUBRO  - TEXTO  - ESTADO - CUIT DE CLIENTE\n");

        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && arrayP[i].estado==0)
                printf("%d - %d - %s - %d - %d\n",arrayP[i].idPublicaciones, arrayP[i].numeroRubro,arrayP[i].texto, arrayP[i].estado,array[i].cuit);
        }
    }
    return retorno;
}

int publicar_alta(Publicaciones* arrayP,int limite,
              Cliente* clientes, int lenClientes)
{
    int retorno = -1;
    int i;
    int idCli;
    int posCli;
    char auxTexto[64];
    int  auxNumero;

    if(limite > 0 && arrayP != NULL)
    {
        i = buscarLugarLibre(arrayP,limite);
        if(i >= 0)
        {


            getValidInt("ID del cliente\n?","\nNumero no valido\n",&idCli,0,99999,2);
            posCli = cliente_buscarPorId(clientes,lenClientes,idCli);
            if(posCli>=0)
            {
                // la cliente existe, idPant es valido

                getValidInt("Numero de Rubro?","\nNumero no valido\n",&auxNumero,0,1000,2);
                getValidString("\nTexto? ","\nEso no es un texto","El maximo es 64",auxTexto,64,2);

                arrayP[i].numeroRubro = auxNumero;
                strcpy(arrayP[i].texto,auxTexto);
                arrayP[i].idCliente = idCli; // relacion
                arrayP[i].estado=0;
                arrayP[i].isEmpty=0;
                arrayP[i].idPublicaciones= proximoId();

                printf("\nEl ID del aviso es:%d\n",arrayP[i].idPublicaciones);
            }
        }
        else
        {
            retorno = -2;
        }

    }
    return retorno;
}


int publicar_baja(Publicaciones* array,int limite, int id)
{
    int indiceAEliminar;
    int retorno=-1;
    indiceAEliminar = buscarPorId(array,limite,id);

    if(indiceAEliminar>=0)
    {

        array[indiceAEliminar].isEmpty=1;
        retorno=0;
    }
    return retorno;
}


static int buscarLugarLibre(Publicaciones* array,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        for(i=0;i<limite;i++)
        {
            if(array[i].isEmpty==1)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}


static int proximoId(void)
{
    static int proximoId = -1;
    proximoId++;
    return proximoId;
}


int buscarPorId(Publicaciones* array,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && array[i].idPublicaciones==id)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

int publicar_cantPublicacionesClientes(Publicaciones* array,int limite,int idCliente)
{
    int i;
    int contadorPublicaciones=0;

    for(i=0;i<limite;i++)
    {
        if(!array[i].isEmpty && array[i].estado==0)
        {
            if(array[i].idCliente==idCliente)
            {
                contadorPublicaciones++;
            }
        }
    }

    return contadorPublicaciones;
}


int publicar_MostrarClienteConPublicacionesActivas(Publicaciones* arrayP,int limiteP,Cliente* array,int limite)
{

    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = 0;
        printf(" ID -  NOMBRE  -  APELLIDO  -    CUIT   -  ESTADO  - CANTIDAD DE PUBLICACIONES\n");
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && arrayP[i].estado==0)
                printf(" %d   - %s   - %s   - %d -  %d  -  %d \n",array[i].idCliente,
                                                                    array[i].nombre,
                                                                    array[i].apellido,
                                                                    array[i].cuit,
                                                                    array[i].isEmpty,
                                                                    publicar_cantPublicacionesClientes(arrayP,limiteP,array[i].idCliente));
        }
    }
    return retorno;

}

int publicar_ClienteConMasPublicacionesActivas(Publicaciones* arrayP,int limiteP,Cliente* array,int limite)
{
    int mayor=0;
    int i;
    int auxCont;
    int retorno=-1;
    if(limite > 0 && array != NULL)
    {   retorno=0;
        if(!array[i].isEmpty && arrayP[i].estado==0)
        {
            auxCont=publicar_cantPublicacionesClientes(arrayP,limiteP,arrayP[i].idCliente);
            for(i=0;i<limite;i++)
            {
                if(auxCont>mayor)
                {
                    mayor=auxCont;
                    printf("el cliente con mas publicaciones es %s",array[i].nombre);
                }
            }

        }
    }

    return retorno;
}


