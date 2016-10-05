#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
    int priority;
    int isLeaf;
    char ch;
    struct node * left;
    struct node * right;
}Tree_Node;


typedef struct tree{
    Tree_Node * root;
    int size;
}Tree;

Tree_Node * create_tree_node(){
    Tree_Node * a = (Tree_Node*)malloc(sizeof(Tree_Node));
    a->left = NULL;
    a->right = NULL;
    a->priority = 0;
    return a;
}
Tree_Node * create_tree_node_1(Tree_Node * a, unsigned int ch){
    a = (Tree_Node*)malloc(sizeof(Tree_Node));
    a->ch = ch;
    a->left = NULL;
    a->right = NULL;
    a->priority = 0;
    return a;
}

Tree * create_tree(){
    Tree *a = (Tree*)malloc(sizeof(Tree));
    a->size = 0;
    a->root = NULL;
    return a;
}
int isLeaf(Tree_Node * tree){
    return tree->isLeaf;
}
void print_preorder_tree(Tree_Node * tree){
    if(tree!=NULL){
        if((tree->ch=='*' || tree->ch=='\\') && isLeaf(tree))
            printf("\\%c", tree->ch);
        else
            printf("%c", tree->ch);
        print_preorder_tree(tree->left);
        print_preorder_tree(tree->right);
    }
}
void print_preorder_tree_in_file(Tree_Node * tree, FILE *file){

    if(tree!=NULL){
        if((tree->ch=='*' || tree->ch=='\\') && isLeaf(tree))
            fprintf(file, "\\%c", tree->ch);
        else
            fprintf(file, "%c", tree->ch);

        print_preorder_tree_in_file(tree->left, file);
        print_preorder_tree_in_file(tree->right,file);
    }

}
/*
void print_content_in_file(char hash[255][20], FILE *file,unsigned char * texto){
    char buffer[20];
    buffer[0]='\0';
    char aux[8];
    aux[0]='\0';
    int i=-1;
    while(texto[++i]!='\0'){

        strcat(buffer,hash[(int)texto[i]]);
        if(strlen(buffer)>=8){
            strncat(aux,buffer,8);
            char ch = (int)strtol(aux,NULL,2);
            printf("aux:%s ch:%c int:%d\n",aux,ch,ch);
            fprintf(file,"%c", ch);
            aux[0]='\0';
            sprintf(buffer,"%s",buffer+8);
        }
    }
    if(strlen(buffer)>0){
        while(strlen(buffer)<8)
            strcat(buffer,"0");
        strncat(aux,buffer,8);
        char ch = (int)strtol(aux,NULL,2);
        printf("aux:%s ch:%c int:%d\n",aux,ch,ch);
        fprintf(file,"%c", ch);
    }
}*/


void print_content_in_file(char hash[256][40], FILE *arq,FILE *file){
    char buffer[60];
    buffer[0]='\0';
    char aux[8];
    aux[0]='\0';
    unsigned int caracter;
    while((caracter = getc(arq))!=EOF){
        //printf ("ch:%d %u\n",caracter,(unsigned char)caracter);
        strcat(buffer,hash[(unsigned char)caracter]);
        //printf("buffer:%s\n",buffer);
        while(strlen(buffer)>=8){
            strncat(aux,buffer,8);
            char ch = (int)strtol(aux,NULL,2);
            //printf("aux:%s ch:%c int:%d\n",aux,ch,ch);
            fprintf(file,"%c", ch);
            aux[0]='\0';
            sprintf(buffer,"%s",buffer+8);
        }
    }
    if(strlen(buffer)>0){
        while(strlen(buffer)<8)
            strcat(buffer,"0");
        strncat(aux,buffer,8);
        char ch = (int)strtol(aux,NULL,2);
        //printf("aux:%s ch:%c int:%d\n",aux,ch,ch);
        fprintf(file,"%c", ch);
    }
}

void printf_first_bits_in_file(char first[16],FILE * file){
    char aux[8];
    strncpy (aux,first,8);
    long long int c1 = strtol(aux,NULL,2);
    long long int c2 = strtol(first+8,NULL,2);
    unsigned char ch1=(int)c1,ch2=(int)c2;
    fprintf(file,"%c%c", ch1,ch2);
}
