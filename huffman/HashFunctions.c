#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"

void create_hash(Tree_Node * tree,char * hash[256],char binary[256]){
    /*Recursivamente, cria o hash utilizando a string binary como auxiliar, a cada vez que vai pra esquerda é adicionado um '0' na string, e pra direita um '1'.*/

    if(isLeaf(tree)){
        hash[(unsigned char)tree->ch] = (char*)malloc(sizeof(char)*(strlen(binary)+1));
        sprintf(hash[(unsigned char)tree->ch],"%s",binary);
    }
    else{
        strcat(binary,"0");
        create_hash(tree->left,hash,binary);
        binary[strlen(binary)-1]='1';
        create_hash(tree->right,hash,binary);
        binary[strlen(binary)-1]='\0';
    }
}
