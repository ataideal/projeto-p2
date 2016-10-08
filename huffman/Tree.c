#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"

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

void print_content_in_file(char hash[256][40], FILE *arq,FILE *file){
    char buffer[60];
    buffer[0]='\0';
    char aux[8];
    aux[0]='\0';
    unsigned int caracter;
    while((caracter = getc(arq))!=EOF){
        strcat(buffer,hash[(unsigned char)caracter]);
        while(strlen(buffer)>=8){
            strncat(aux,buffer,8);
            char ch = (int)strtol(aux,NULL,2);
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

int size_tree(Tree_Node* tree){
	if(tree==NULL)
        return 0;
    return 1 + size_tree(tree->left) + size_tree(tree->right);
}

unsigned int get_trash_size(FILE *input_file) {
	unsigned int trash_size = 0;
	unsigned int first_byte;
	fseek(input_file, 0, SEEK_SET);
	first_byte = getc(input_file);
	trash_size = (unsigned int)(first_byte >> (5));
	return (trash_size);
}

unsigned int get_tree_size(FILE *input_file) {
	unsigned int tree_size;
	unsigned char first_byte;
	unsigned int second_byte;

	fseek(input_file, 0, SEEK_SET); /* volta ao início do arquivo */

	/* recebe os dois primeiros bytes do arquivo */
	first_byte = getc(input_file);
	second_byte = getc(input_file);

	/* apaga os três primeiros bits do primeiro byte, pois só interessa os 5
	 * bits restantes */
	first_byte = (first_byte << 3);
	first_byte = (first_byte >> 3);

	/* o tamanho da árvore é a união entre os 5 últimos bits do primeiro byte
	 * e o segundo byte */
	tree_size = ((first_byte << 8) | second_byte);

	return (tree_size); /* retorna o valor que estava escrito */
}

unsigned int *get_tree_array(FILE *input_file, unsigned int * tree_size) {
    unsigned int i;

	/* cria um array com o tamanho da árvore recebido */
	unsigned int *tree_array;
    tree_array = (unsigned int *)malloc(sizeof(unsigned int)*((*tree_size)+2));
	/* vai até o terceito byte do arquivo para receber os caracteres (o ter-
	 * ceiro byte é o primeiro byte da árvore) */
	fseek(input_file, 2, 0);

	/* recebe os caracteres em sequencia tree_size vezes */
	for (i = 0; i < (*tree_size); i++) {
	tree_array[i] = getc(input_file);
        if(tree_array[i] == '\\'){
            (*tree_size)++;
            i++;
            tree_array[i] = getc(input_file);
        }
    }

    for (i = 0; i < (*tree_size); i++) {
            printf("%c",tree_array[i]);
    }
	return (tree_array); /* retorna o endereço para o array criado */
}

Tree_Node* fill_tree(Tree_Node * tree, unsigned int * vetor,int *atual,int tamanho){
    //printf ("%d ",*atual);
    if(*atual>tamanho)
        return NULL;

    if(vetor[*atual]=='\\' && (vetor[(*atual)+1]=='\\' || vetor[(*atual)+1]=='*')){
        (*atual)++;
        tree = create_tree_node_1(tree,vetor[*atual]);
        tree->isLeaf=1;
        (*atual)++;
        return tree;
    }

    if(tree==NULL)
        tree = create_tree_node_1(tree,vetor[*atual]);

    if(vetor[*atual]=='*'){
        (*atual)++;
        tree->isLeaf=0;
        tree->left = fill_tree(tree->left,vetor,atual,tamanho);
        tree->right = fill_tree(tree->right,vetor,atual,tamanho);
    }else{
        (*atual)++;
        tree->isLeaf=1;
    }

    return tree;
}

Tree_Node *get_tree(FILE *input_file){
    unsigned int tree_size = get_tree_size(input_file);
	/* recebe o array com a árvore em pré-ordem */
	unsigned int *tree_array;
	tree_array = get_tree_array(input_file, &tree_size);

    Tree_Node * tree = NULL;
    int atual=0;
    printf ("\n");
    tree = fill_tree(tree,tree_array,&atual,tree_size);
    printf ("\n%d\n",tree_size);
    print_preorder_tree(tree);

    return tree;
}

