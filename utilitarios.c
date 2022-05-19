#include "utilitarios.h"

booleano abrirArchivo (FILE **fp, const char *nom, const char *modo)
{
    *fp = fopen(nom, modo);

    if (!*fp)
        return falso;

    return TODO_OK;
}

/// duda
void intercambio (void *d1, void *d2, size_t tam)
{
   void *aux = malloc (tam);

   if (!aux)
        return;

   memcpy(aux, d1,tam);
   memcpy(d1, d2, tam);
   memcpy(d2, aux, tam);

   free(aux);
}


void ordenar_burbujeo (void *dato, size_t ce, size_t tam, Cmp cmp)
{
    void *aux=dato;
    int i,
        j;

    for (i=0; i< ce; i++)
    {
        dato=aux;
        for (j=0; j<ce-1 ; j++, dato+=tam)
            if (cmp( dato, (dato+tam))  > 0)
                intercambio( dato, (dato+tam), tam );
    }

}

void ordenar_seleccion ()
{

}
