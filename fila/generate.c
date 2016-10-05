#include <stdio.h>
#include <stdlib.h>
#include "generate.h"


FILE *gerar_crescente (FILE *crescente)
{
    int i=0;

    crescente = fopen("Entrada_crescente.txt","a");
        for(i=0;i<100000;i++)
        {
            fprintf(crescente,"%d\n",i);
        }
    return crescente;
}

FILE *gerar_decrescente(FILE *decrescente)
{
    int i=0;

    decrescente = fopen("Entrada_decrescente.txt","a");
        for(i=99999;i>=0;i--)
        {
            fprintf(decrescente,"%d\n",i);
        }

        return decrescente;
}
