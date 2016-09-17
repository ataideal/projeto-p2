#include <stdio.h>
#include <stdlib.h>
#include "priority_queue_heap.h"

struct Element
{
    int num;
    int priority;
};

struct Heap
{
    int size;
    int priority;
    int current_size;
    struct Element *data;
};

typedef struct Element Element;
typedef struct Heap Heap;

void view_size (Heap *heap)
{
    if(heap->size==heap->current_size-1)
    {
        heap->current_size*=2;

        heap->data = (Element*) realloc (heap->data,heap->current_size*sizeof(Element));
    }
}

int get_parent_index(Heap *heap, int i)
{
    return i/2;
}
int get_left_index(Heap *heap, int i)
{
    return 2*i;
}
int get_right_index(Heap *heap, int i)
{
    return 2*i + 1;
}
Heap *create_heap()
{
    Heap *aux = (Heap *) malloc (sizeof (Heap));
    aux->size=0;
    aux->current_size=12;
    aux->data = (Element*) calloc (12,sizeof(Element));

    return aux;
}

int value_of(Heap *heap, int i)
{
    return heap->data[i].num;
}
void swap (int *i, int *j)
{

    int aux = *i;
    *i = *j;
    *j = aux;
}

void enqueue_heap (Heap *heap, int priority, int value)
{


        heap->data[++heap->size].priority = priority;
        heap->data[heap->size].num= value;
        view_size(heap);

        int key_index = heap->size;
        int parent_index = get_parent_index(heap,heap->size);

        while (parent_index>=1 && heap->data[key_index].priority > heap->data[parent_index].priority)
        {
            swapData(&heap->data[key_index],&heap->data[parent_index]);

            key_index = parent_index;

            parent_index = get_parent_index(heap,key_index);
        }


}

int dequeue_heap (Heap *heap)
{
    if(heap->size==0)
    {
        printf ("Heap Vazia!\n");
        return 0;
    }
    int value = heap->data[1].num;
    heap->data[1]=heap->data[heap->size];
    heap->size--;
    max_heapify(heap,1);
    return value;
}

void swapData(Element * a, Element * b){
    Element aux=*a;
    *a = *b;
    *b = aux;
}

void max_heapify(Heap *heap, int i)
{
    int largest;
    int left_index = get_left_index(heap, i);
    int right_index = get_right_index(heap, i);

    if(left_index <= heap->size && heap->data[left_index].priority > heap->data[i].priority)
    {
        largest=left_index;
    }
    else
    {
        largest=i;
    }

    if(right_index <= heap->size && heap->data[right_index].priority > heap->data[largest].priority)
    {
        largest = right_index;
    }

    if (heap->data[i].priority != heap->data[largest].priority)
    {
        swapData(&heap->data[i], &heap->data[largest]);
        max_heapify(heap,largest);
    }
}

void heapsort(Heap *heap)
{
    int i;
    for(i=heap->size;i>=2;i--)
    {
        swapData(&heap->data[1],&heap->data[i]);
        heap->size--;
        max_heapify(heap,1);
    }
}
