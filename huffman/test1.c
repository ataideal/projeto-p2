#include <stdio.h>
#include <stdlib.h>

int main (){
    FILE *arq = fopen("output1.txt","wb+");
    int i;
    for(i=0;i<256;i++)
        fprintf (arq,"%c%c",i,i);

    return 0;
}
