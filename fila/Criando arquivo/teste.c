#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main ()
{
    int element;
    FILE *arq;

    arq = fopen("dados_entrada_aleatorio.txt", "a");
    if(arq==NULL)
    {
        printf ("Nao deu\n");
        return ;
    }

    int i;
        for(i=0;i<100000;i++)
        {
            element = rand()%100000;
            fprintf(arq,"%d\n",element);
        }




    fclose(arq);
    printf ("Dados gravados!\n");


    return 0;
}
