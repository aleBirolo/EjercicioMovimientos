#include "movimiento.h"

booleano esFechaValida (const t_fecha *fec)
{

    if (!(fec->aa >= 1600 && fec->aa <= 3000))
        return falso;

    if ( !(fec->mm>= 1 && fec->mm<=12) )
        return falso;

    if (!(fec->dd>= 1 && fec->dd<=31))
        return falso;

    if (fec->mm == 4 || fec->mm == 6 ||fec->mm == 9 ||fec->mm == 10)
        if (fec->dd == 31)
            return falso;

    if (fec->mm == 2)
    {
        if (ES_BISIESTO(fec->aa))
        {
            if (fec->dd > 28)
                return falso;
        }
        else
        {
            if (fec->dd > 29)
                return falso;
        }

    }
    return verdadero;
}


t_fecha generarFecha (int i)
{
    static t_fecha fec;
    if (i == 0)
    {
        fec.aa = rand() % 22 + 2000;
        fec.dd = rand() % 31 + 1;
        fec.mm = rand() % 12 + 1;
    }

    /// 0 : se mantiene la fecha
    /// 1 : aumenta 1 dia
    /// 2 : aumenta 1 mes (si salen 2 veces un 2)
    /// 3 : aumenta 1 año (si salen 3 veces un 3)
    switch (rand() % 4)
    {
        case 0:
            break;
        case 1:
            if ( fec.dd + 1 >31 )
            {
                if (fec.mm +1 > 12)
                {
                    fec.aa++;
                    fec.mm=1;
                    fec.dd=1;
                }
                else
                {
                    fec.mm++;
                    fec.dd=1;
                }
            }
            else
                fec.dd++;
            break;
        case 2:
            if (rand() % 4 == 2 && rand() % 4 == 2)
            {
                if (fec.mm + 1 >12)
                {
                    fec.mm = 1;
                    fec.aa++;
                }
                else
                    fec.mm++;
            }
            break;
        case 3:
            if (rand() % 4 == 3 && rand() % 4 == 3 && rand() % 4 == 3)
                fec.aa++;
            break;
        default:
            break;
    }

    if (!esFechaValida(&fec))
        fec.dd=1;

    return fec;
}

t_hora generarHora ()
{
    t_hora hora;

    hora.hh = rand() % 24;
    hora.mm = rand() % 60;
    hora.ss = rand() % 60;

    return hora;
}

char * generarSucursal()
{
    char *suc,
         suc_Tot[][TAM_SUC]={{"bco1"},
                             {"bco2"},
                             {"bco3"},
                             {"bco4"},
                             {"banco5"},
                            };

    suc=suc_Tot[ rand() % 5 ];

    return suc;
}

char * generarCliente()
{
    char *cli,
         cli_Tot[][TAM_SUC]={{"cli1"},
                             {"cli2"},
                             {"cli3"},
                             {"cli4"},
                             {"cli5"},
                             {"cli6"},
                             {"cliente7"},
                             {"cli8"},
                             {"cli9"},
                             {"cli10"},
                            };

    cli=cli_Tot[ rand() % 10 ];

    return cli;
}

int compararSubCadena (const char *s1, const char *s2, char car)
{
    int  cant_1,
         cant_2;

    cant_1 = (char *)strchr(s1,car) - s1;
    cant_2 = (char *)strchr(s2,car) - s2;

    if (cant_1 != cant_2)
        return cant_1 - cant_2;

    return strncmp(s1, s2, cant_1 );
}

int compararFecha_creacion (const t_fecha f1, const t_fecha f2)
{
    int cmp;

    cmp = f1.aa - f2.aa;
    if (cmp == 0)
    {
        cmp = f1.mm - f2.mm;
        if (cmp == 0)
            cmp = f1.dd - f2.dd;
    }

    return cmp;
}

/*
int compararFecha (const char *s1, const char *s2, char car)
{
    t_fecha f1,
            f2;
    char aux_s1[11] = {},
         aux_s2[11] = {},
         *cad_1,
         *cad_2;

    /// hago una copia de la cadena porque no la quiero cortar
    strcpy(aux_s1, s1);
    strcpy(aux_s2, s2);

    cad_1 = strrchr (aux_s1, car);
    f1.dd = sscanf(cad_1 +1, "%d");
    *cad_1='\0';

    cad_1 = strrchr (aux_s1, car);
    f1.mm = sscanf(cad_1 +1, "%d");
    *cad_1='\0';

    f1.mm = sscanf(aux_s1, "%d");
    *cad_1='\0';



    return 0;
}
*/
int compararMovimientos_creacion (const void *m1, const void *m2 )
{
    t_mov *mov_1 = (t_mov *)m1,
          *mov_2 = (t_mov *)m2;
    int cmp;

    /// Comparacion por codigo de cuenta limpio
    cmp = compararSubCadena (mov_1->cuenta, mov_2->cuenta, '/');
    if ( cmp == 0)
    {
        /// Comparacion por codigo de sucursal limpio
        cmp = compararSubCadena ( strchr (mov_1->cuenta, '/') + 1 , strchr (mov_2->cuenta, '/') + 1, '\0');
        if (cmp == 0)
        {
            /// Comparacion por fecha
            cmp = compararFecha_creacion ( mov_1->fecha , mov_2->fecha);
        }
    }


    return cmp;
}

void generarMovimientos (t_mov *mov, size_t cantMov)
{
    int i;

    for (i=0; i<cantMov ; i++)
    {
        mov[i].fecha = generarFecha(i);
        mov[i].hora = generarHora();
        strcpy ( mov[i].cuenta, generarCliente() );
        strcat ( mov[i].cuenta, "/");
        strcat ( mov[i].cuenta, generarSucursal());
        mov[i].tipoMov =  rand() % 2 == 0 ? 'D' :'E';
        mov[i].monto =(float) rand() * ( rand() %10000 + 1  ) /100;
    }

    #ifdef GENERAR_ARCHIVO_ORDENADO
        ordenar_burbujeo(mov,cantMov, sizeof(t_mov),compararMovimientos_creacion );
    #endif
}

void mostrarMovimientos (t_mov *mov, size_t cantMov)
{
    int i;

    for (i=0 ; i<cantMov ; i++)
    {
        printf ("%d/%d/%d %d:%d:%d %s %c %.2f\n",
                mov[i].fecha.dd,
                mov[i].fecha.mm,
                mov[i].fecha.aa,
                mov[i].hora.hh,
                mov[i].hora.mm,
                mov[i].hora.ss,
                mov[i].cuenta,
                mov[i].tipoMov,
                mov[i].monto
               );
    }
}

booleano grabarArchivoTXTMov (FILE *fp, t_mov *mov, size_t cantMov)
{
    int i;

    for (i=0; i<cantMov; i++)
    {
        fprintf(fp, "%d/%d/%d %d:%d:%d %s %c %.2f\n",
                mov[i].fecha.dd,
                mov[i].fecha.mm,
                mov[i].fecha.aa,
                mov[i].hora.hh,
                mov[i].hora.mm,
                mov[i].hora.ss,
                mov[i].cuenta,
                mov[i].tipoMov,
                mov[i].monto
               );
    }

    return TODO_OK;
}



