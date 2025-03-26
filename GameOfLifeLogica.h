#ifndef GAMEOFLIFELOGICA_H_INCLUDED
#define GAMEOFLIFELOGICA_H_INCLUDED

#include <string.h>
#include <Windows.h>
#include <time.h>

#define TODO_OK 0
#define ERR_ARCH 1
#define ERR_MEM 2
#define TAM_CELULA 10

typedef struct
{
    char **m;
    unsigned char filas;
    unsigned char columnas;
}TMatriz;

void ingresoTam(TMatriz*,char*[]);
char** construirMatriz(unsigned,unsigned);
void destruirMatriz(char**, unsigned);
int leerInicio(TMatriz*,char*[]);
void sigGen(TMatriz*);
void genVida(TMatriz*,int,int);
void genVidaBorde(TMatriz*,int,int);
void iniciarSDLauto(TMatriz*,int,int);
void iniciarSDLmanual(TMatriz*);
void matrizRandom(TMatriz*);
void mostrarMenuPrincipal();
int mostrarMenuContinua(TMatriz*);
void mostrarMenuAvance(TMatriz*);
void mostrarMenuDemos(TMatriz*);
void avanzarManual(TMatriz*);
void avanzarAutomatico(TMatriz*);
void demoSapo(TMatriz*);
void demoPlaneador(TMatriz*);
void demoPulsar(TMatriz*);
void demoCanionDePlaneadores(TMatriz*);
void iniciarSDLauto(TMatriz*,int,int);
void iniciarSDLmanual(TMatriz*);
void moverAlCentro(TMatriz*,size_t,size_t);

#endif // GAMEOFLIFELOGICA_H_INCLUDED
