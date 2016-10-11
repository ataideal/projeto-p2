/*
 * File:   newcunittest.c
 * Author: tiago
 *
 * Created on 10/10/2016, 12:46:49
 */

#include <stdio.h>
#include <stdlib.h>
#include <C:\cunit\CUnit-2.1-2\CUnit\Headers\CUnit.h>
#include <C:\cunit\CUnit-2.1-2\CUnit\Headers\Basic.h>
#include "pq.h"

/*
 * CUnit Test Suite
 */
priorityQueue* pq;
int init_suite(void) {
    pq = createPriorityQueue();
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testDequeue() {
    pq = enqueue(pq,1,10);
    CU_ASSERT_EQUAL(dequeue(pq),1);
    pq = enqueue(pq,10,2);
    CU_ASSERT_EQUAL(dequeue(pq),1);
    pq = enqueue(pq,8,12);
    CU_ASSERT_EQUAL(dequeue(pq),8);
    pq = enqueue(pq,2,5);
    CU_ASSERT_EQUAL(dequeue(pq),8);
}

void testEnqueue() {
    
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("newcunittest", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }   

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testDequeue", testDequeue)) ||
            (NULL == CU_add_test(pSuite, "testEnqueue", testEnqueue))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
