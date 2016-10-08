#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"

void create_hash(Tree_Node * tree,char hash[256][40],char binary[40]){
    if(isLeaf(tree)){
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
