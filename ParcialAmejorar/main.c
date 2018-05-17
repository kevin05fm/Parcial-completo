#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "cliente.h"
#include "utn.h"
#include "publicaciones.h"

#define CANT 100
#define LEN_CONT    1000

int main()
{
    Cliente array[CANT];
    Publicaciones arrayP[LEN_CONT];

    int menu;
    int auxiliarId;
    int auxEstado;
    int i;
    int indicePublicacion;
    int indiceCliente;
    cliente_init(array,CANT);
    publicar_init(arrayP,LEN_CONT);


    do
    {
        getValidInt("\n\n1.Alta\n2.Modificar\n3.Baja\n4.Realizar una Publicacion\n5.Pausar Publicacion\n6.Reanudar Publicacion\n7.Imprimir Clientes\n8.Imprimir Publicacion\n9. \n10.Salir\n","\nNo valida\n",&menu,1,10,1);
        switch(menu)
        {
            case 1:
                cliente_alta(array,CANT);
                break;
            case 2:
                getValidInt("ID?","\nID Incorrecto\n",&auxiliarId,0,200,2);
                cliente_modificacion(array,CANT,auxiliarId);

                break;
            case 3:
                getValidInt("ID?","\nID Incorrecto\n",&auxiliarId,0,200,2);

                cliente_baja(array,CANT,auxiliarId);
                break;
            case 4:
                publicar_alta(arrayP,LEN_CONT,
                array, CANT);

                break;
            case 5:
                getValidInt("ID publicacion?","\nID Incorrecto\n",&auxiliarId,0,200,2);
                indicePublicacion=buscarPorId(arrayP,LEN_CONT,auxiliarId);
                indiceCliente=cliente_buscarPorId(array,CANT,arrayP[indicePublicacion].idCliente);
                printf(" %d   - %s   - %s   - %d -     %d \n",array[indiceCliente].idCliente, array[indiceCliente].nombre,array[indiceCliente].apellido,array[indiceCliente].cuit,array[indiceCliente].isEmpty);
                getValidInt("Quiere pausar la publicacion?\n1.Si\n2.No","\nNumero no valido\n",&auxEstado,0,1,2);
                if(auxEstado==1)
                {
                    for(i=0;i<LEN_CONT;i++)
                    {
                        arrayP[auxiliarId].estado=1;
                    }

                    printf("El Estado se encuentra pausado");
                }


                break;
            case 6:
                getValidInt("ID publicacion?","\nID Incorrecto\n",&auxiliarId,0,200,2);
                indicePublicacion=buscarPorId(arrayP,LEN_CONT,auxiliarId);
                indiceCliente=cliente_buscarPorId(array,CANT,arrayP[indicePublicacion].idCliente);
                printf(" %d   - %s   - %s   - %d -     %d \n",array[indiceCliente].idCliente, array[indiceCliente].nombre,array[indiceCliente].apellido,array[indiceCliente].cuit,array[indiceCliente].isEmpty);
                getValidInt("Quiere reanudar la publicacion?\n1.Si\n2.No","\nNumero no valido\n",&auxEstado,0,1,2);
                if(auxEstado==1)
                {
                    for(i=0;i<LEN_CONT;i++)
                    {
                        arrayP[auxiliarId].estado=0;
                    }

                    printf("El Estado se encuentra activo");
                }


                break;
            case 7:
               publicar_MostrarClienteConPublicacionesActivas(arrayP,LEN_CONT,array,CANT);

                break;
            case 8:
                publicar_mostrarActivos(arrayP,LEN_CONT,array,CANT);
                break;
            case 9:
                publicar_ClienteConMasPublicacionesActivas(arrayP,LEN_CONT,array,CANT);
                break;
            case 10:

               break;

        }

    }while(menu != 10);

    return 0;
}


