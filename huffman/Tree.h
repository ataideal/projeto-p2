#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

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

Tree_Node * create_tree_node();
Tree * create_tree();
void print_preorder_tree(Tree_Node * tree);
void print_preorder_tree_in_file(Tree_Node * tree, FILE *file);
void print_content_in_file(char hash[255][20], FILE *file,unsigned char * texto);

#endif // TREE_H_INCLUDED
