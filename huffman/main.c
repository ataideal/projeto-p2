#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PriorityQueue.h"
#include "Tree.h"

int isLeaf(Tree_Node * tree){
    return tree->isLeaf;
}

void create_hash(Tree_Node * tree,char hash[255][20],char binary[20]){
    if(isLeaf(tree)){

        sprintf(hash[(int)tree->ch[0]],"%s",binary);
    }
    else{
        strcat(binary,"0");
        create_hash(tree->left,hash,binary);
        binary[strlen(binary)-1]='1';
        create_hash(tree->right,hash,binary);
        binary[strlen(binary)-1]='\0';
    }
}
/**< apsokdopaskdopasokpdopsadsda */
int main(){
    printf("Huffman!\n");
    unsigned char texto[100];
    scanf ("%[^\n]",texto);
    int i;
    int vetor[256];

    for(i=0;i<256;i++){
        vetor[i]=0;
    }

    for(i=0;texto[i];i++){
        vetor[texto[i]]++;
    }

    //qsort(vetor,256,sizeof(Contar),cmpfunc);
    Priority_Queue * pq = create_priority_queue(); // fazer priority queue de nodes

    for(i=0;i<256;i++){
        if(vetor[i] !=0){
            Tree_Node * a = create_tree_node();
            a->priority = vetor[i];
            a->isLeaf=1;
            sprintf(a->ch,"%c",i);
            pq = enqueue_pq(pq,a);
        }
            //printf ("char:%c freq:%d\n",vetor[i].ch,vetor[i].frequency);
    }
    //
    while(size_pq(pq)>1){
        Tree_Node * x1 = dequeue_pq(pq);
        Tree_Node * x2 = dequeue_pq(pq);
        Tree_Node * p = create_tree_node();
        p->priority = x1->priority + x2->priority;
        p->right = x1;
        p->left = x2;
        p->isLeaf=0;
        sprintf(p->ch,"*");
        pq = enqueue_pq(pq,p);
    }

    Tree * tree = create_tree();
    tree->root = dequeue_pq(pq);
    //print_preorder_tree(tree->root);

    char hash[255][20];
    char binary [20];
    binary[0]='\0';
    create_hash(tree->root,hash,binary);

    FILE *output_file;
    output_file = fopen("output.txt", "wb+");
    print_preorder_tree_in_file(tree->root,output_file);
    print_content_in_file(hash,output_file,texto);
    fclose(output_file);



    return 0;
}
