#include <stdio.h>
#include <stdlib.h>
#include <priority_queue.h>

int main()
{

   priorityQueue *pq;
   pq = createPriorityQueue();

    int i;
    int b,d;
        for(i=0;i<5;i++)
        { scanf ("%d %d", &b,&d);
            enqueue(pq,b,d);
        }

        printQueue(pq);


    printf("Hello world!\n");
    return 0;
}
