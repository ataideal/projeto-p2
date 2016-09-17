#ifndef PRIORITY_QUEUE_HEAP_H_INCLUDED
#define PRIORITY_QUEUE_HEAP_H_INCLUDED

typedef struct Heap Heap;
typedef struct Element Element;


Heap *create_heap();
int get_parent_index(Heap *heap,int i);
int get_left_index(Heap *heap,int i);
int get_right_index(Heap *heap,int i);

int value_of(Heap *heap, int i);

void enqueue_heap (Heap *heap,int priority,int value);
int dequeue_heap (Heap *heap);

void max_heapify(Heap *heap, int i);
void heapsort (Heap *heap);

void swapData(Element * a, Element * b);

#endif // PRIORITY_QUEUE_HEAP_H_INCLUDED
