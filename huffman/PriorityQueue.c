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


Priority_Queue * create_priority_queue(){
    Priority_Queue * pq = (Priority_Queue*)malloc(sizeof(Priority_Queue));
    pq->size = 0;
    pq->first = NULL;
    return pq;
}
int size_pq (Priority_Queue * pq){
    return pq->size;
}

int pq_is_empty (Priority_Queue * pq){
    return pq->first == NULL;
}

Priority_Queue * enqueue_pq(Priority_Queue * pq,Tree_Node * a){
    PQ_Node * newnode = (PQ_Node*)malloc(sizeof(PQ_Node));
    pq->size++;
    newnode->item = a;
    newnode->priority = a->priority;
    if(pq_is_empty(pq) || pq->first->priority > a->priority){
        newnode->next = pq->first;
        pq->first = newnode;
        return pq;
    }
    PQ_Node * aux = pq->first;

    while(aux->next!=NULL && aux->next->priority < a->priority){
        aux = aux->next;
    }
    newnode->next = aux->next;
    aux->next = newnode;
    return pq;
}

Tree_Node * dequeue_pq(Priority_Queue * pq){
    pq->size--;
    Tree_Node * aux = pq->first->item;
    pq->first = pq->first->next;
    return aux;
}
