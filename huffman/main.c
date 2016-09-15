#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int priority;
    char ch[100];
    struct node * left;
    struct node * right;
}Node;

struct node_pq{
    Node * element;
    int frequency;
    struct node_pq * next;
}

int main()
{
    printf("Huffman!\n");
    unsigned char texto[100];
    scanf ("%[^\n]",texto);
    int i;
    int t = strlen(texto);
    int vetor[256];

    for(i=0;i<256;i++){
        vetor[i]=0;
    }

    for(i=0;texto[i];i++){
        vetor[texto[i]]++;
    }

    //qsort(vetor,256,sizeof(Contar),cmpfunc);
    PriorityQueue pq = create_priority_queue(); // fazer priority queue de nodes

    for(i=0;i<256;i++){
        if(vetor[i] !=0){
            Tree_Node * a = create_tree_node();
            a.priority = vetor[i];
            sprintf(a.ch,"%c",i);
            enqueue_pq(pq,a);
        }
            //printf ("char:%c freq:%d\n",vetor[i].ch,vetor[i].frequency);
    }
    //
    while(size_pq(pq)>1){
        Tree_Node * x1 = dequeue(pq);
        Tree_Node * x2 = dequeue(pq);

        Tree_Node * p = create_tree_node();
        p.priority = x1.priority + x2.priority;
        p.left = x1;
        p.right = x2;
        sprintf(p.ch,"%s+%s",x1.ch,x2.ch);
        insert_pq(pq,p);
    }

    Tree * tree = create_tree();
    tree.root = dequeue(pq);



    return 0;
}
