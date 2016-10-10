#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"
#include "priority_queue_heap.h"
#include "generate.h"

int main()
{
   if( remove( "generate_output_heap.txt" ) != 0 )
    perror( "Error deleting file" );
   else
    puts( "File successfully deleted" );

   if( remove( "generate_output_pq.txt" ) != 0 )
    perror( "Error deleting file" );
   else
    puts( "File successfully deleted" );
   priorityQueue *pq;
   pq = createPriorityQueue();
   Heap *newHeap = create_heap();

   int i=0;
    srand(time(NULL));
   for(i=0;i<1000;i++)
   {

       int element = rand()%1000;
       printf ("Element : %d\n",element);
       enqueue(pq,element,element);
       enqueue_heap(newHeap,element,element);
   }
   printf ("Dados criados!\n");



    return 0;
}
