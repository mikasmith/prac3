#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "bst.h"

#define MATCH comparison == 0
#define IN_LEFT comparison < 0
#define IN_RIGHT comparison > 0


struct bst_node{
    char *key;
    bst left;
    bst right; 
};

bst bst_new(){
    return NULL; 
}

bst bst_insert(bst b, char *str){
    int comparison;
    
    if(b == NULL){
        b = emalloc(sizeof *b);
        b->left= NULL;
        b->right = NULL;
        b->key= emalloc(strlen(str)+1 *sizeof str[0]);
        strcpy(b->key, str);
        
    }
    
    comparison=strcmp(str, b->key);

    if(IN_LEFT){
        b->left = bst_insert(b->left, str);
    }else if(IN_RIGHT){
        b->right = bst_insert(b->right, str);
    }
    return b;    
}

int bst_search(bst b, char *key){
    int comparison;
    if (b == NULL) return 0;
    comparison = strcmp(key, b->key);

    if(MATCH){
        return 1;
    }else if(IN_LEFT){
        return bst_search(b->left, key);
    }else if(IN_RIGHT){
        return bst_search(b->right, key);
    }else{
        exit(EXIT_FAILURE);
    }
}

void bst_inorder(bst b, void f(char *s)){
    if(b!=NULL){
        bst_inorder(b->left, f);
        f(b->key);
        bst_inorder(b->right, f);
    }

}

void bst_preorder(bst b, void f(char *s)){
    if(b!=NULL){
        f(b->key);
        bst_preorder(b->left, f);
        bst_preorder(b->right, f);
    }

}

bst bst_free(bst b) {
    if (b == NULL) return NULL;
    free(b->key);

    bst_free(b->left);
    bst_free(b->right);
    free(b);

    return b;
}

