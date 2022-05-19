#ifndef MOVIMIENTO_H_INCLUDED
#define MOVIMIENTO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilitarios.h"

#define GENERAR_ARCHIVO_ORDENADO

#ifdef GENERAR_ARCHIVO_ORDENADO
    #define FILE_T_1 "movimientoOrdenado.txt"
#else
    #define FILE_T_1 "movimientoSinOrderar.txt"
#endif

#define FILE_B_2 "Mov_Tot_Mayor_A_10_M.bin"
#define FILE_B_3 "Mov_Tot_Menor_A_10_M.bin"

#define TAM_MOV 1000
#define TAM_NRO_CUENTA 10
#define TAM_SUC 10
#define TAM_CUENTA TAM_NRO_CUENTA + TAM_SUC + 1
#define TAM_LINEA 500

#define MONTO_TOTAL_DIEZ_M 10000000
typedef struct
{
    unsigned dd,
             mm,
             aa;
}t_fecha;

typedef struct
{
    unsigned hh,
             mm,
             ss;
}t_hora;

typedef struct
{
    t_fecha fecha;
    t_hora hora;
    char cuenta[TAM_CUENTA],
         tipoMov;
    float monto;
}t_mov;

typedef struct
{
    char cuenta[TAM_CUENTA];
    float monto;
}t_cuenta_monto;

t_fecha generarFecha (int i);
t_hora generarHora ();
char * generarSucursal();
char * generarCliente();
int compararFecha_creacion (const t_fecha f1, const t_fecha f2);

int compararMovimientos_creacion (const void *m1, const void *m2 );

void generarMovimientos (t_mov *mov, size_t cantMov);
void mostrarMovimientos (t_mov *mov,size_t cantMov);
booleano grabarArchivoTXTMov (FILE *fp, t_mov *mov, size_t cantMov);


#endif // MOVIMIENTO_H_INCLUDED
