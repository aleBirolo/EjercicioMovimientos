#include "main.h"


int main()
{
    t_mov movi[TAM_MOV]={};
    t_cuenta_monto ctaMto;

    FILE *fp_mov,
         *fp_mov_mayores,
         *fp_mov_menores;

    int cantMov=1000;

    char linea[TAM_LINEA]={},
         cuenta[TAM_CUENTA]={},
         cuenta_sig[TAM_CUENTA]={};

    float acumMonto = 0,
          monto_sig;

    booleano flag_archivo_con_un_linea;

    //srand(time(NULL));

    if (generarLote_Archivo (movi, &fp_mov, cantMov) != TODO_OK)
        printf ("\n Error al generear lote");
    else
        printf ("\n Lote generado correctamente.\n");

    printf ("\n Archivo de movimientos: \n\n");
    mostrarMovimientos(movi, cantMov);
    printf ("\n\n");
    system("pause");
    system("cls");

    if (abrirArchivo(&fp_mov, FILE_T_1, "r") != TODO_OK )
    {
        printf ("\n Error al abrir archivo %s en modo %s", FILE_T_1, "r" );
        return ERROR_ABRIR_ARCHIVO;
    }

    if (abrirArchivo(&fp_mov_mayores, FILE_B_2, "wb") != TODO_OK )
    {
        printf ("\n Error al abrir archivo %s en modo %s", FILE_B_2, "wb" );
        return ERROR_ABRIR_ARCHIVO;
    }

    if (abrirArchivo(&fp_mov_menores, FILE_B_3, "wb") != TODO_OK )
    {
        printf ("\n Error al abrir archivo %s en modo %s", FILE_B_3, "wb" );
        return ERROR_ABRIR_ARCHIVO;
    }

    if (fgets(linea, TAM_LINEA, fp_mov))
    {
        flag_archivo_con_un_linea = verdadero;

        /// monto
        acumMonto+= getMonto(linea);

        /// Cuenta
        strcpy(cuenta, getCuenta(linea));
    }


    while (fgets(linea, TAM_LINEA, fp_mov) )
    {
        flag_archivo_con_un_linea = falso;

        /// monto
        monto_sig = getMonto(linea);

        /// Cuenta
        strcpy(cuenta_sig, getCuenta(linea));

        if (strcmp(cuenta, cuenta_sig) == 0)
            acumMonto += monto_sig;

        else
        {
            strcpy (ctaMto.cuenta, cuenta);
            ctaMto.monto = acumMonto;

            if (acumMonto >= MONTO_TOTAL_DIEZ_M)
                fwrite(&ctaMto,sizeof(t_cuenta_monto),1,fp_mov_mayores);
            else
                fwrite(&ctaMto,sizeof(t_cuenta_monto),1,fp_mov_menores);

            acumMonto = monto_sig;
            strcpy(cuenta, cuenta_sig);
        }
    }

    if (flag_archivo_con_un_linea)
    {
        strcpy (ctaMto.cuenta, cuenta);
        ctaMto.monto = acumMonto;

        if (acumMonto >= MONTO_TOTAL_DIEZ_M)
            fwrite(&ctaMto,sizeof(t_cuenta_monto),1,fp_mov_mayores);
        else
            fwrite(&ctaMto,sizeof(t_cuenta_monto),1,fp_mov_menores);
    }

    fclose(fp_mov);
    fclose(fp_mov_mayores);
    fclose(fp_mov_menores);

    if (abrirArchivo(&fp_mov_mayores, FILE_B_2, "rb") != TODO_OK )
    {
        printf ("\n Error al abrir archivo %s en modo %s", FILE_B_2, "rb" );
        return ERROR_ABRIR_ARCHIVO;
    }

    printf ("\n Archivo con mayores:\n\n");
    fread(&ctaMto,sizeof(t_cuenta_monto),1,fp_mov_mayores );

    while (!feof (fp_mov_mayores))
    {
        printf ("%s %.2f\n", ctaMto.cuenta, ctaMto.monto);
        fread(&ctaMto,sizeof(t_cuenta_monto),1,fp_mov_mayores );
    }

    fclose(fp_mov_mayores);


    if (abrirArchivo(&fp_mov_menores, FILE_B_3, "rb") != TODO_OK )
    {
        printf ("\n Error al abrir archivo %s en modo %s", FILE_B_3, "rb" );
        return ERROR_ABRIR_ARCHIVO;
    }

    printf ("\n Archivo con menores:\n\n");
    fread(&ctaMto,sizeof(t_cuenta_monto),1,fp_mov_menores );

    while (!feof (fp_mov_menores))
    {
        printf ("%s %.2f\n", ctaMto.cuenta, ctaMto.monto);
        fread(&ctaMto,sizeof(t_cuenta_monto),1,fp_mov_menores );
    }

    fclose(fp_mov_menores);

    return 0;
}

/// monto
float getMonto (char *linea)
{
    char *campo;
    float saldo;

    campo = strrchr (linea,' ');
    saldo= atof (campo);
    *campo = '\0';

    return saldo;
}

char * getCuenta (char *linea)
{
    char *campo;

    /// tipo de movimiento
    campo = strrchr (linea,' ');
    *campo = '\0';

    /// cuenta
    campo = strrchr (linea,' ');

    return campo+1;
}

booleano generarLote_Archivo (t_mov *movi, FILE **fp_mov, int cantMov)
{
    generarMovimientos(movi, cantMov);
    if (abrirArchivo(fp_mov, FILE_T_1, "w") != TODO_OK )
    {
        printf ("\n Error al abrir archivo %s en modo %s", FILE_T_1, "w" );
        return ERROR_ABRIR_ARCHIVO;
    }

    grabarArchivoTXTMov(*fp_mov, movi, cantMov);
    fclose(*fp_mov);

    return TODO_OK;
}



