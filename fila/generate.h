#ifndef GENERATE_H_INCLUDED
#define GENERATE_H_INCLUDED

void generate_cresc(FILE *arquivo)
{
    arquivo = fopen ("dados_entrada_crescente","a");
    if(arquivo==NULL)
    {
        return 0;
    }
    int i;
        for(i=0;i<100000;i++)
        {
            fprintf(arquivo,"%d\n",i);
        }
    fclose(arquivo);
}


#endif // GENERATE_H_INCLUDED
