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
            aux->next=pq->First;
            pq->First = aux;
        }
        else
        {   Node *current;
            current=pq->First;

            while(current->next!=NULL && current->next->priority>p)
            {
                current=current->next;
            }
            aux->next=current->next;
            current->next=aux;

        }
        return pq; //Pois tem que atualizar a cabe�a da fila mesmo que n�o tenha sido inserido em ultimo ou primeiro.
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
