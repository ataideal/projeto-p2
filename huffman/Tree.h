#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

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

Tree_Node * create_tree_node();
Tree * create_tree();
void print_preorder_tree(Tree_Node * tree);
void print_preorder_tree_in_file(Tree_Node * tree, FILE *file);


#endif // TREE_H_INCLUDED
