#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int priority;
    char ch[100];
    struct node * left;
    struct node * right;
}Node;

typedef struct contar{
    int frequency;
    char ch;
}Contar;

int cmpfunc (const void * a, const void * b)
{
   return ( (*(Contar*)a).frequency - (*(Contar*)b).frequency );
}

int main()
{
    printf("Huffman!\n");
    char texto[100];
    scanf ("%[^\n]",texto);
    int i;
    int t = strlen(texto);
    Contar vetor[256];

    for(i=0;i<256;i++){
        vetor[i].frequency=0;
        //vetor[i].ch = '*';
    }

    for(i=0;texto[i];i++){
        vetor[texto[i]+128].frequency++;
        vetor[texto[i]+128].ch = texto[i];
    }

    //qsort(vetor,256,sizeof(Contar),cmpfunc);
    PriorityQueue pq = newPq(); // fazer priority queue de nodes

    for(i=0;i<256;i++){
        if(vetor[i].frequency !=0){
            Node * a = (Node*)malloc(sizeof(Node));
            a.left = NULL;
            a.right= NULL;
            a.priority = vetor[i].frequency;
            sprintf(a.ch,"%c",vetor[i].ch);
            insert_pq(pq,a);
        }
            //printf ("char:%c freq:%d\n",vetor[i].ch,vetor[i].frequency);
    }
    //
    while(size_pq(pq)>1){
        Node * x1 = dequeue(pq);
        Node * x2 = dequeue(pq);

        Node * p = (Node*)malloc(sizeof(Node));
        p.priority = x1.priority + x2.priority;
        p.left = x1;
        p.right = x2;
        sprintf(p.ch,"%s+%s",x1.ch,x2.ch);
        insert_pq(pq,p);
    }

    Node * tree = dequeue(pq);



    return 0;
}
