#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PriorityQueue.h"
#include "Tree.h"

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
        p->left = x1;
        p->right = x2;
        sprintf(p->ch,"*",x1->ch,x2->ch);
        pq = enqueue_pq(pq,p);
    }

    Tree * tree = create_tree();
    tree->root = dequeue_pq(pq);
    print_preorder_tree(tree->root);
    FILE *output_file;
    output_file = fopen("output.txt", "wb+");
    print_preorder_tree_in_file(tree->root,output_file);
    fclose(output_file);

    return 0;
}
