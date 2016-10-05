#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

struct Node
{
    int element;
    int priority;
    struct Node *next;
};

typedef struct Node Node;
struct priorityQueue
{
    int size;
    int compara;
    int maxSize;
    Node *First;
};
typedef struct priorityQueue priorityQueue;

int isEmpty (priorityQueue *pq)
{
    return (pq->First==NULL);
}

priorityQueue *createPriorityQueue()
{
    priorityQueue *newP = (priorityQueue*) malloc (sizeof(priorityQueue));
    newP->First=NULL;
    newP->compara=0;
    newP->size=0;
    newP->maxSize=100;
    return newP;
}

priorityQueue *enqueue (priorityQueue *pq, int elemento, int p)
{
    Node *aux;
    aux = (Node*) malloc (sizeof (Node));
    aux->element=elemento;
    aux->priority=p;
        if(isEmpty(pq) || p > pq->First->priority)
        {
            if(!isEmpty(pq)) pq->compara++;
            aux->next=pq->First;
            pq->First = aux;
        }
        else
        {   Node *current;
            current=pq->First;

            while(current->next!=NULL && current->next->priority>p)
            {
                pq->compara++;
                current=current->next;
            }
            aux->next=current->next;
            current->next=aux;

        }
        pq->size++;

        if(pq->size==pq->maxSize)
        {
            FILE *aux;
                aux=fopen("generate_output_pq.txt","a");
            fprintf(aux,"%d %d\n",pq->size,pq->compara);
            fclose(aux);

            pq->compara=0;
            pq->maxSize+=100;
        }

        return pq; //Pois tem que atualizar a cabeça da fila mesmo que não tenha sido inserido em ultimo ou primeiro.
}

int dequeue (priorityQueue *pq)
{
    if(!isEmpty(pq))
    {
        int i=pq->First->element;
        Node *current = pq->First;
        pq->First = pq->First->next;
        free(current);

        return i;
    }
    else
    {
        printf ("empty");
    }
    return 0;
}

void printQueue (priorityQueue *pq)
{
    Node *aux;
    aux=pq->First;
        while(aux!=NULL)
        {
            printf("PriorityQueue - %d\n",aux->element);
            aux=aux->next;
        }

}
