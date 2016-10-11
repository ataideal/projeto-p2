#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "pq.h"

priorityQueue * pq;

int init_suite1(void)
{
   pq = NULL;
   pq = createPriorityQueue();
   if(pq==NULL)
      return -1;
    return 0;
}

int clean_suite1(void)
{
   while(!isEmpty(pq))
        dequeue(pq);

   free(pq);
   return 0;
}

void testEnqueue_Dequeue(void)
{
    pq = enqueue(pq,1,10);
    pq = enqueue(pq,8,2);
    pq = enqueue(pq,20,9);
    CU_ASSERT_EQUAL(dequeue(pq),1);
    pq = enqueue(pq,11,15);
    CU_ASSERT_EQUAL(dequeue(pq),11);
    CU_ASSERT_EQUAL(dequeue(pq),20);
    CU_ASSERT_EQUAL(dequeue(pq),8);
}

void testEmpty(void)
{
    CU_ASSERT_EQUAL(isEmpty(pq),1);
    CU_ASSERT_EQUAL(pq->size,0);
}

int main()
{
   CU_pSuite pSuite = NULL;

   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if ((NULL == CU_add_test(pSuite, "test enqueue and dequeue", testEnqueue_Dequeue)) ||
       (NULL == CU_add_test(pSuite, "test testEmpty", testEmpty)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
