#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"


struct htablerec {
    int capacity;
    int numkeys;
    char **keys;
};


htable htable_new(int size) {
    int i;
    htable result = emalloc(sizeof *result); /*declare htable, allocate memory*/
    result->capacity = size;  
    result->numkeys = 0;
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);
    
    for(i=0; i < size; i++){
        result->keys[i] = NULL;
    }
    
    return result;
}

static unsigned int htable_word_to_int(char *word){
    unsigned int result=0;
    while(*word != '\0'){
        result= (*word++ + 31 * result);
    }
    return result;
}



int htable_insert(htable h, char *str) {
    unsigned int val = htable_word_to_int(str);
    int rem = val % (unsigned int)h->capacity;
    int init = rem;

    do{
        
        if(h->keys[rem]== NULL){ 
            h->keys[rem] = emalloc((strlen(str)+1) * sizeof str[0]);
            strcpy(h->keys[rem], str);
            h->numkeys++; 
            return 1;
        }else if(strcmp(h->keys[rem], str) != 0){
            rem= (rem+1)%h->capacity;
        }
    }while(rem != init);

    return 0;
}



void htable_print(htable h, FILE *stream) {
    int i;
    for (i = 0; i < h->capacity; i++) {
        fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
    } 
}


void htable_free(htable h) {   
    int i;
    for(i=0; i < h->capacity; i++){
        free(h->keys[i]);
    }
    free(h->keys);
    free(h);  
}
