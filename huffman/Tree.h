#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

struct node{
    int priority;
    int isLeaf;
    char ch;
    struct node * left;
    struct node * right;
};
typedef struct node Tree_Node;

struct tree{
    Tree_Node * root;
    int size;
};
typedef struct tree Tree;

Tree_Node* create_tree_node();
Tree_Node* create_tree_node_1(Tree_Node * a,unsigned int ch);
Tree* create_tree();
int isLeaf(Tree_Node * tree);
void print_preorder_tree(Tree_Node * tree);
void print_preorder_tree_in_file(Tree_Node * tree, FILE *file);
void print_content_in_file(char hash[256][40], FILE *arq,FILE *file);
void printf_first_bits_in_file(char first[16],FILE * file);
int size_tree(Tree_Node* tree);
unsigned int get_trash_size(FILE *input_file);
unsigned int get_tree_size(FILE *input_file);
unsigned int* get_tree_array(FILE *input_file, unsigned int * tree_size);
Tree_Node* fill_tree(Tree_Node * tree, unsigned int * vetor,int *atual,int tamanho);
Tree_Node* get_tree(FILE *input_file);

#endif // TREE_H_INCLUDED
