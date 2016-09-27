#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"
typedef struct q_item *q_item;

struct q_item {
    double item;
    q_item next;
};

struct queue {
    q_item first;
    q_item last;
    int length;
};

queue queue_new() {
    int default_size = 7;
    queue result = emalloc(sizeof *result);
    result->length = default_size; 
    return result; 
}

void enqueue(queue q, double item) {
    q_item i = emalloc(sizeof *i);
    i->item = item;
    i->next = NULL;
    if (q->length == 0) {
        q->first = i;
    } else {
        q->last->next = i;
    }
    q->last = i;
    q->length++;
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
    /* print queue contents one per line to 2 decimal places */
    int i;
    for (i = 0; i < q->length; i++) {
        if(q->items[i]!=0){
            printf("%.2f\n", q->items[i]);
        }
    }
}

void queue_print_info(queue q) {
    if (q->length == 0) {
        printf("The queue is empty\n");
    } else {
        printf("first %.2f, last %.2f, length %d\n", q->first->item,
               q->last->item, q->length);
    }
}

int queue_size(queue q) {
    return q->length; 
}

void queue_free_aux(q_item i) {
    free(i); 
}

queue queue_free(queue q) {
    free(q);
    
    return q; 
}
