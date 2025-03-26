#include "GameOfLife.h"
#include "GameOfLifeLogica.h"

void mostrarMenuPrincipal()
{
    system("cls");
    printf("\n==== Juego de la Vida de Conway ====\n");
    printf("1. Cargar configuracion inicial desde archivo\n");
    printf("2. Ver demos (Planeador, Sapo, Pulsar, Canion de planeadores)\n");
    printf("3. Generar una configuracion al azar \n");
    printf("4. Salir\n");
}

int mostrarMenuContinua(TMatriz* camp)
{
    int opcion;
    system("cls");
    printf("\n==== Menu Principal ====\n");
    printf("1. Volver a jugar\n");
    printf("2. Salir\n");

    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    getchar();

    if(opcion<1 || opcion>2){
      do{
            system("cls");
            printf("\n==== Menu Principal ====\n");
            printf("1. Volver a jugar\n");
            printf("2. Salir\n");
            printf("Opcion invalida. Intente nuevamente.\n");
            printf("Seleccione una opcion: ");
            scanf("%d", &opcion);
            getchar();
        } while(opcion<1 || opcion>2);
    }
    else if(opcion == 2)
        opcion -= 2;

    return (opcion);
}

void mostrarMenuAvance(TMatriz* matriz)
{
    int opcion;
    system("cls");
    printf("\n==== Opciones de Avance ====\n");
    printf("1. Avanzar manualmente generacion a generacion\n");
    printf("2. Avanzar automaticamente\n");
    printf("3. Volver al menu principal\n");

    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    getchar();

    if(opcion<1 || opcion>3){
      do{
            system("cls");
            printf("\n==== Opciones de Avance ====\n");
            printf("1. Avanzar manualmente generacion a generacion\n");
            printf("2. Avanzar automaticamente\n");
            printf("3. Volver al menu principal\n");
            printf("Opcion invalida. Intente nuevamente.\n");
            printf("Seleccione una opcion: ");
            scanf("%d", &opcion);
            getchar();

    } while(opcion<1 || opcion>3);
    }


    switch (opcion)
    {
        case 1:
            avanzarManual(matriz);
            break;
        case 2:
            avanzarAutomatico(matriz);
            break;
        case 3:
            return;
        default:

            break;
    }
}

void mostrarMenuDemos(TMatriz *matriz)
{
    int opcion;
    system("cls");
    printf("\n==== Demos ====\n");
    printf("1. Planeador\n");
    printf("2. Sapo\n");
    printf("3. Pulsar\n");
    printf("4. Canion de planeadores\n");
    printf("5. Volver al menu principal\n");

    printf("Seleccione una demo: ");
    scanf("%d", &opcion);
    getchar();

     if(opcion<1 || opcion>5){
      do{
            system("cls");
            printf("\n==== Demos ====\n");
            printf("1. Planeador\n");
            printf("2. Sapo\n");
            printf("3. Pulsar\n");
            printf("4. Canion de planeadores\n");
            printf("5. Volver al menu principal\n");
            printf("Opcion invalida. Intente nuevamente.\n");
            printf("Seleccione una opcion: ");
            scanf("%d", &opcion);
            getchar();

    } while(opcion<1 || opcion>5);
    }

    switch (opcion)
    {
        case 1:
            demoPlaneador(matriz);
            break;
        case 2:
            demoSapo(matriz);
            break;
        case 3:
            demoPulsar(matriz);
            break;
        case 4:
            demoCanionDePlaneadores(matriz);
            break;
        case 5:
            return;
        default:

            break;
    }


}

void demoSapo(TMatriz *matriz)
{
 int col=6,fil=6,medf=(matriz->filas-fil)/2,medc=(matriz->columnas-col)/2;
    char sapo[][6]={{0,0,0,0,0,0},
                    {0,0,1,0,0,0},
                    {0,1,0,0,1,0},
                    {0,1,0,0,1,0},
                    {0,0,0,1,0,0},
                    {0,0,0,0,0,0}
                    };

    for (int i = 0; i < fil; i++)
        memcpy(&matriz->m[i+medf][medc],sapo[i],col*sizeof(char));

    mostrarMenuAvance(matriz);
}

void demoPlaneador(TMatriz *matriz)
{
    char planeador[][6]={{0,0,1,0,0,0},
                          {1,0,1,0,0,0},
                          {0,1,1,0,0,0},
                          {0,0,0,0,0,0},
                          {0,0,0,0,0,0}
                        };
    for (int i = 0; i < 5; i++)
        memcpy(matriz->m[i], planeador[i], 6 * sizeof(char));
    mostrarMenuAvance(matriz);
}

void demoPulsar(TMatriz *matriz)
{
    int col=17,fil=17,medf=(matriz->filas-fil)/2,medc=(matriz->columnas-col)/2;
    char pulsar[][17]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
                       {0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
                       {0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,1,1,1,0,0,1,1,0,1,1,0,0,1,1,1,0},
                       {0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0},
                       {0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},
                       {0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0},
                       {0,1,1,1,0,0,1,1,0,1,1,0,0,1,1,1,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},
                       {0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
                       {0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
                     };
    for (int i = 0; i < fil; i++)
        memcpy(&matriz->m[i+medf][medc],pulsar[i],col*sizeof(char));
    mostrarMenuAvance(matriz);
}

void demoCanionDePlaneadores(TMatriz *matriz)
{
    int col=36,fil=16,medf=(matriz->filas-fil)/2,medc=(matriz->columnas-col)/2;
    char canion[][36]={{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
                       {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1},
                       {0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,1},
                       {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
                      };
    for (int i = 0; i < fil; i++)
        memcpy(&matriz->m[i+medf][medc],canion[i],col*sizeof(char));
    mostrarMenuAvance(matriz);
}

void moverAlCentro(TMatriz* matriz, size_t f, size_t c)
{
    int medf = (matriz->filas - f) / 2;
    int medc = (matriz->columnas - c) / 2;

    for (int i = f - 1; i >= 0; i--)
    {
        memmove(&matriz->m[i + medf][medc], &matriz->m[i][0], c * sizeof(char));
        memset(&matriz->m[i][0], 0, c * sizeof(char));
    }

}
