#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "movimiento.h"

booleano generarLote_Archivo (t_mov *movi, FILE **fp_mov, int cantMov);

float getMonto (char *linea);
char * getCuenta (char *linea);

#endif // MAIN_H_INCLUDED
