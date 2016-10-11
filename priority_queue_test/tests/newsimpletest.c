/*
 * File:   newsimpletest.c
 * Author: tiago
 *
 * Created on 10/10/2016, 12:40:41
 */

#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

/*
 * Simple C Test Suite
 */

void testCreatePriorityQueue() {
    priorityQueue* result = createPriorityQueue();
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testCreatePriorityQueue (newsimpletest) message=error message sample\n");
    }
}

void testDequeue() {
    priorityQueue* pq;
    int result = dequeue(pq);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testDequeue (newsimpletest) message=error message sample\n");
    }
}

void testEnqueue() {
    priorityQueue* pq;
    int elemento;
    int p;
    priorityQueue* result = enqueue(pq, elemento, p);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testEnqueue (newsimpletest) message=error message sample\n");
    }
}

void testIsEmpty() {
    priorityQueue* pq;
    int result = isEmpty(pq);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testIsEmpty (newsimpletest) message=error message sample\n");
    }
}

void testPrintQueue() {
    priorityQueue* pq;
    printQueue(pq);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testPrintQueue (newsimpletest) message=error message sample\n");
    }
}

int main(int argc, char** argv) {


    return (EXIT_SUCCESS);
}
