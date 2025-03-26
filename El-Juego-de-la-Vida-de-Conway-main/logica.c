#include "GameOfLife.h"
#include "GameOfLifeLogica.h"

void ingresoTam(TMatriz *matriz,char *argv[])
{
    matriz->filas = atoi(argv[1]);

    matriz->columnas = atoi(argv[2]);
}

char** construirMatriz(unsigned f, unsigned c)
{
    char** mat, **ini;
    mat = calloc(f,sizeof(char*));//puntero a arreglo de enteros *int
    if(!mat)
        return NULL;
    ini = mat;
    for(int i = 0; i < f; i++)
    {
        *mat = calloc(c,sizeof(char));
        if(!*mat)
        {
            for(int j = 0; j < i; j++)
                free(*(mat+j));
            free(mat);
            return NULL;
        }
        mat++;
    }
    return ini;
}

void destruirMatriz(char** mat, unsigned f)
{
   for(int i = 0; i < f; i++)
        free(*(mat+i));

    free(mat);
}

int leerInicio(TMatriz* matriz,char *argv[])
{
    int i = 0, j,columnas = 0;
    char *linea = malloc(sizeof(char) * (matriz->columnas + 1));
    FILE *inicio;

    if(!linea)
        return ERR_MEM;

    inicio = fopen(argv[3], "rt");

    if (!inicio)
    {
        free(linea);
        return ERR_ARCH;;
    }

    while (fgets(linea,matriz->columnas + 1,inicio))
    {
        columnas = strlen(linea) - 1;

        for(j = 0; j < columnas; j++)
            matriz->m[i][j] = *(linea + j) - '0';

        i++;
    }

    free(linea);

    fclose(inicio);

    moverAlCentro(matriz, i + 1, columnas + 1);

    return 0;
}

void sigGen(TMatriz* matriz)
{

    for (int i = 1; i < matriz->filas - 1; i++)//solo centro
    {
        for (int j = 1; j < matriz->columnas - 1; j++)
        {
            genVida(matriz, i, j);
        }
    }

    // borde columna
    for (int i = 0; i < matriz->filas; i++)
    {
        genVidaBorde(matriz, i, 0);
        genVidaBorde(matriz, i, matriz->columnas - 1);
    }
    //borde fila
    for (int j = 0; j < matriz->columnas; j++)
    {
        genVidaBorde(matriz, 0, j);
        genVidaBorde(matriz, matriz->filas - 1, j);
    }


    for (int i = 0; i < matriz->filas; i++)
    {
        for (int j = 0; j < matriz->columnas; j++)
        {
            matriz->m[i][j] = (matriz->m[i][j] >= 2) ? 1 : 0;
        }
    }
}

void genVida(TMatriz* matriz,int i,int j)
{
    int v = 0;
    //valor pasado -> valor futuro
    //00 muerto->muerto
    //01 vivo->muerto
    //10 muerto->vivo
    //11 vivo->vivo
    for(int x = i-1; x < i + 2; x++)
    {
        for(int y = j-1; y < j + 2; y++)
        {
            if(x != i || y != j)
                v += matriz->m[x][y] % 2;
        }
    }

    if( !(matriz->m[i][j]) && (v == 3))
        matriz->m[i][j] += 2;

    else if((matriz->m[i][j]) && (v == 2||v == 3))
        matriz->m[i][j] += 2;
}

void genVidaBorde(TMatriz* matriz,int i,int j)
{
    int v = 0;
    //valor pasado -> valor futuro
    //00 muerto->muerto
    //01 vivo->muerto
    //10 muerto->vivo
    //11 vivo->vivo
    for(int x = i-1; x < i + 2; x++)
    {
        for(int y = j-1; y < j + 2; y++)
        {
            if((x >= 0 && x < matriz->filas) && (y >= 0 && y <matriz->columnas) && (x != i || y != j))
                v += matriz->m[x][y] % 2;
        }
    }

    if( !(matriz->m[i][j]) && (v == 3))
        matriz->m[i][j] += 2;

    else if((matriz->m[i][j]) && (v == 2||v == 3))
        matriz->m[i][j] += 2;
}

void iniciarSDLmanual(TMatriz *matriz)
{
    unsigned char done=0;
    int k;
    char op;

    SDL_Window* window      = NULL;
    SDL_Renderer* renderer  = NULL;
    SDL_Event e;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL No se ha podido inicializar! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Juego de la vida",
                                                SDL_WINDOWPOS_UNDEFINED,
                                                SDL_WINDOWPOS_UNDEFINED,
                                                TAM_CELULA*matriz->columnas,
                                                TAM_CELULA*matriz->filas,
                                                SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Error en la creacion de la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("No se ha podido crear el lienzo! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    while (!done && op != 's'){ //Se puede parar tambien cuando no se observen cambios!
        while (SDL_PollEvent(&e) != 0) {

            if (e.type == SDL_QUIT) {
                done = 1;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0x01, 0x02, 0x3A, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

        for (int y = 0; y < matriz->filas; y++) {
            for (int x = 0; x < matriz->columnas; x++)
            {
                if (matriz->m[y][x])
                {
                    SDL_SetRenderDrawColor(renderer, 0xEE, 0xE6, 0x2B, 0xFF); // Color para la célula viva
                    SDL_Rect cell = { x * TAM_CELULA, y * TAM_CELULA, TAM_CELULA, TAM_CELULA };
                    SDL_RenderFillRect(renderer, &cell);
                }
            }
        }

        SDL_RenderPresent(renderer);
        k++;
        SDL_UpdateWindowSurface(window);

        fflush(stdin);
        op = getc(stdin);

        sigGen(matriz);

        SDL_SetWindowTitle(window, "Juego de la Vida de Conway (pulse ´s´ para salir)");

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

void iniciarSDLauto(TMatriz *matriz,int gen, int delay)
{
    unsigned char done=0;
    int k;

    SDL_Window* window      = NULL;
    SDL_Renderer* renderer  = NULL;
    SDL_Event e;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL No se ha podido inicializar! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Juego de la vida",
                                                SDL_WINDOWPOS_UNDEFINED,
                                                SDL_WINDOWPOS_UNDEFINED,
                                                TAM_CELULA*matriz->columnas,
                                                TAM_CELULA*matriz->filas,
                                                SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Error en la creacion de la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("No se ha podido crear el lienzo! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    while (!done && gen){ //Se puede parar tambien cuando no se observen cambios!
        while (SDL_PollEvent(&e) != 0) {

            if (e.type == SDL_QUIT) {
                done = 1;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0x01, 0x02, 0x3A, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

        for (int y = 0; y < matriz->filas; y++) {
            for (int x = 0; x < matriz->columnas; x++)
            {
                if (matriz->m[y][x])
                {
                    SDL_SetRenderDrawColor(renderer, 0xEE, 0xE6, 0x2B, 0xFF); // Color para la célula viva
                    SDL_Rect cell = { x * TAM_CELULA, y * TAM_CELULA, TAM_CELULA, TAM_CELULA };
                    SDL_RenderFillRect(renderer, &cell);

                }

            }
        }

        SDL_RenderPresent(renderer);
        k++;
        //SDL_UpdateWindowSurface(window);

        sigGen(matriz);

        SDL_SetWindowTitle(window, "Juego de la Vida de Conway");
        SDL_Delay(delay);

        gen--;

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

////////////////////////////////////////////////


void avanzarManual(TMatriz* matriz)
{
    system("cls");

    printf("\nAvanzar a la siguiente generacion (presione cualquier tecla para avanzar, 's' para salir): ");

    iniciarSDLmanual(matriz);

}

void avanzarAutomatico(TMatriz* matriz)
{
    unsigned delay, cont ;
    printf("\nIngrese el tiempo de retraso entre generaciones (en milisegundos): ");
    scanf("%d", &delay);

    printf("\nIngrese cuantas generaciones desea ver: ");
    scanf("%d", &cont);

    iniciarSDLauto(matriz,cont,delay);
}

void matrizRandom(TMatriz* matriz)
{
    unsigned char i, j;
    srand(time(NULL));
    matriz->m = construirMatriz(matriz->filas,matriz->columnas);

    for(i = 0; i < matriz->filas; i++)
    {
        for(j = 0; j < matriz->columnas; j++)
        {
            matriz->m[i][j] = (rand() % 2);
        }
    }
}
