#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"

struct queue {
    double *items;
    int head;
    int capacity;
    int num_items;
};

queue queue_new() {
    int default_size = 7, i;
    queue result = emalloc(sizeof *result);
    result->capacity = default_size;
    result->num_items=0;
    result->head = 0; 
    result->items = emalloc(result->capacity * sizeof result->items[0]);

    for(i=0; i < result->capacity; i++){
        result->items[i] = 0;
    }
    
    return result; 
}

void enqueue(queue q, double item) {
    if (q->num_items < q->capacity) {
        q->items[(q->head + q->num_items++) % q->capacity] = item;
    }
}

double dequeue(queue q) {
    if(q-> num_items > 0){
        return q->items[q->head];
        q->head=(q->head+1)%q->capacity;    
        q->num_items--;
    }
    return EXIT_SUCCESS; 
}

void queue_print(queue q) {
    int i;
    for (i = q->head; i < (q->head + q->num_items); i++) {
        if(q->items[i]!=0){
            printf("%.2f\n", q->items[i]);
        }
    }
    
}

void queue_print_info(queue q) {
    int i;
    printf("capacity %d, num_items %d, head %d\n[", q->capacity,
           q->num_items, q->head);
    for (i = 0; i < q->capacity; i++) {
        printf("%s%.2f", i == 0 ? "" : ", ", q->items[i]);
    }
    printf("]\n");
}

int queue_size(queue q) {
    return q->num_items; 
}

queue queue_free(queue q) {
    /*int i;
    for(i=0; i < q->capacity; i++){
        free(q->items[i]);
        }*/
    free(q);
    
    return q; 
}
