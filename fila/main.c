#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"
#include "priority_queue_heap.h"

int main()
{

   priorityQueue *pq;
   pq = createPriorityQueue();
   Heap *newHeap = create_heap();
    int i;
        for(i=0;i<50;i++)
        {
            enqueue(pq,i,i);
            enqueue_heap(newHeap,i,i);
        }

        printQueue(pq);
        for(i=0;i<50;i++)
        {
            printf ("Heap Queue - %d\n",dequeue_heap(newHeap));
        }

    return 0;
}
