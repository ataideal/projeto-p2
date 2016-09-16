#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"

typedef struct pq_node{
    Tree_Node * item;
    struct pq_node * next;
    int priority;
}PQ_Node;

typedef struct priority_queue{
    PQ_Node * first;
    int size;
}Priority_Queue;

Priority_Queue * create_priority_queue();
int size_pq (Priority_Queue * pq);
Priority_Queue * enqueue_pq(Priority_Queue * pq,Tree_Node * a);
Tree_Node * dequeue_pq(Priority_Queue * pq);

#endif // PRIORITYQUEUE_H_INCLUDED
