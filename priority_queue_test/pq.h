#ifndef PQ_H_INCLUDED
#define PQ_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

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
    Node *First;
};
typedef struct priorityQueue priorityQueue;

int isEmpty (priorityQueue *pq);
priorityQueue *createPriorityQueue();
priorityQueue *enqueue (priorityQueue *pq, int elemento, int p);
int dequeue (priorityQueue *pq);
void printQueue (priorityQueue *pq);


#endif // PQ_H_INCLUDED
