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
    queue result = emalloc(sizeof *result);
    result->length = 0;
    result->first = NULL;
    result->last = NULL;
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
    double result; 
    if(q->length > 0){
        result= q->first->item;
        q->first= q->first->next;    
        q->length--;
    }else{
        return EXIT_SUCCESS;
    }
    return result; 
}

void queue_print(queue q) {
    int i;
    q_item key = q->first;
    for (i = 0; i < q->length; i++) {
        printf("%.2f\n", key->item);
        key= key->next;       
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
    if(i!=NULL){
        queue_free_aux(i->next);
        free(i);
    }     
}

queue queue_free(queue q) {
    queue_free_aux(q->first);
    free(q);    
    return q; 
}
