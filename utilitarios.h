#ifndef UTILITARIOS_H_INCLUDED
#define UTILITARIOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define TODO_OK 1

#define ES_BISIESTO(x) ( x%4== 0 ? ( ( x%100 == 0) ? ( (x%400 == 0) ? 1 : 0 ) : 1 ) : 0)
#define ERROR_ABRIR_ARCHIVO 455



typedef enum
{
    verdadero=1,
    falso =0
}booleano;

typedef int (*Cmp)(const void *d1, const void *d2);

booleano abrirArchivo (FILE **fp, const char *nom, const char *modo);
void intercambio (void *d1, void *d2, size_t tam);
void ordenar_burbujeo (void *dato, size_t ce, size_t tam, Cmp cmp);
void ordenar_seleccion ();

#endif // UTILITARIOS_H_INCLUDED
