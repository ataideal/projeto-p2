#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
    int priority;
    int isLeaf;
    char ch[100];
    struct node * left;
    struct node * right;
}Tree_Node;


typedef struct tree{
    Tree_Node * root;
}Tree;

Tree_Node * create_tree_node(){
    Tree_Node * a = (Tree_Node*)malloc(sizeof(Tree_Node));
    a->left = NULL;
    a->right = NULL;
    a->priority = 0;
    return a;
}
Tree * create_tree(){
    Tree *a = (Tree*)malloc(sizeof(Tree));
    a->root = NULL;
    return a;
}

void print_preorder_tree(Tree_Node * tree){
    if(tree!=NULL){
        printf ("%s:%d\n",tree->ch,tree->priority);
        print_preorder_tree(tree->left);
        print_preorder_tree(tree->right);
    }
}
void print_preorder_tree_in_file(Tree_Node * tree, FILE *file){

    if(tree!=NULL){
        if(strcmp(tree->ch,"*")!=0)
            fprintf(file, "%s", tree->ch);
        else
            fprintf(file, "%s", tree->ch);
        print_preorder_tree_in_file(tree->left, file);
        print_preorder_tree_in_file(tree->right,file);
    }

}

void print_content_in_file(char hash[255][20], FILE *file,unsigned char * texto){
    int i=-1;
    while(texto[++i]!='\0'){
        fprintf(file,"%s", hash[(int)texto[i]]);
    }
}
