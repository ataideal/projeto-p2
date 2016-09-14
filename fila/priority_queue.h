#ifndef PRIORITY_QUEUE_H_INCLUDED
#define PRIORITY_QUEUE_H_INCLUDED

typedef struct Node Node;
typedef struct priorityQueue priorityQueue;

int isEmpty (priorityQueue *pq);
priorityQueue *createPriorityQueue();
priorityQueue *enqueue (priorityQueue *pq, int elemento, int p);
int dequeue (priorityQueue *pq);
void printQueue (priorityQueue *pq);

#endif // PRIORITY_QUEUE_H_INCLUDED
