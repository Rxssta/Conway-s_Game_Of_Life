#include "GameOfLife.h"
#include "GameOfLifeLogica.h"

//  ACLARACIÓN: Los parámetros se envian con el formato filas columnas nombreArchivo
//  Ejemplo: 100 100 "Inicio.txt"

int main(int argc, char *argv[])
{
    int opcion,continua = 1;
    TMatriz matriz;
    while(continua)
    {
        system("cls");
        ingresoTam(&matriz, argv);

        matriz.m = construirMatriz(matriz.filas,matriz.columnas);

        if(continua)
        {
            mostrarMenuPrincipal();
            printf("Seleccione una opcion: ");
            scanf("%d", &opcion);
            getchar();

            if(opcion<1 || opcion>4){
          do{
                mostrarMenuPrincipal();
                printf("Opcion invalida. Intente nuevamente.\n");
                printf("Seleccione una opcion: ");
                scanf("%d", &opcion);
                getchar();

        } while(opcion<1 || opcion>4);
        }

            switch (opcion)
            {
                case 1:
                    if(leerInicio(&matriz,argv))
                        return ERR_MEM;
                    mostrarMenuAvance(&matriz);
                    break;
                case 2:
                    mostrarMenuDemos(&matriz);
                    break;
                case 3:
                    matrizRandom(&matriz);
                    mostrarMenuAvance(&matriz);
                    break;
                case 4:
                    printf("Saliendo del programa...\n");
                    continua = 0;
                    break;

            }
            destruirMatriz(matriz.m,matriz.filas);
        }
    }

    return 0;
}


