#include <stdio.h>
#include <stdlib.h>

int main (){
    FILE *arq = fopen("output.txt","rb");
    unsigned int ch;

    while((ch=fgetc(arq))!= EOF){
        printf ("char:%c int:%d\n",ch,ch);
    }
    getchar();
    return 0;
}
