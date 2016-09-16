#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int priority;
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
