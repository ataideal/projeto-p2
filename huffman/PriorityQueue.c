#include <stdio.h>
#include <stdlib.h>
#include "Tree.c"

typedef struct node{
    Tree_Node * item;
    struct node * next;
    int priority;
}PQ_Node;

typedef struc PriorityQueue{
    PQ_Node * first;
    int size;
}Priority_Queue;


Priority_Queue * create_priority_queue(){
    Priority_Queue pq = (Priority_Queue*)malloc(sizeof(Priority_Queue));
    pq->size = 0;
    pq->first = NULL;
    return pq;
}
int size_pq (PriorityQueue * pq){
    return pq->size;
}
void enqueue_pq(PriorityQueue * pq,Tree_Node * a){
    PQ_Node * aux = pq->first;
    while(aux!=NULL){
        //if(aux->pri)
    }
}
