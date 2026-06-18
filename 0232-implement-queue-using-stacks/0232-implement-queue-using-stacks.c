#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXE 255

typedef struct Queue {
    int head;
    int tail;
    int tab[MAXE];
} Queue;

typedef Queue MyQueue;


//Init queue
MyQueue *myQueueCreate() {
    MyQueue *queue = malloc(sizeof(MyQueue));

    if (queue == NULL){
        printf("Error initialize a queue.\nConsider checking u're pc <3");
        return NULL;
    }

    queue->tail = 0;    
    queue->head = 0;

    return queue;

}


bool myQueueEmpty(MyQueue *queue) {
    return queue->head == queue->tail;
}


void PrintMyQueue(MyQueue *queue) {
    int i = queue->tail;
    printf("[");
    while(i < queue->head) {
        char c = (i < queue->head-1) ? ',' : '\0';
        printf("%d%c", queue->tab[i], c); //Like go with comma at this end of slice
        i++;
    }
    printf("]\n");
}



int myQueuePop(MyQueue* queue) {
    if (myQueueEmpty(queue)) {
        printf("U can't pop on empty queue");
        return -1;
    } else {
        return queue->tab[queue->tail++];
    }
}


void myQueuePush(MyQueue *queue, int x) {
    if (queue->head+1 >= 256) {
        printf("This queue is full !\n");
    } else {
        queue->tab[queue->head++] = x;;
    }
}

int myQueuePeek(MyQueue* queue) {
    if (myQueueEmpty(queue)) {
        printf("Queue's empty");
        return -1;
    } else {
        return queue->tab[queue->tail];
    }
}


void myQueueFree(MyQueue *queue) {
    free(queue);
}