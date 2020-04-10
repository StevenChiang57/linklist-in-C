#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

dnode* dnode_create(int data, dnode* prev, dnode* next){
    dnode* p = (dnode*)malloc(sizeof(dnode));
    p->data = data;
    p->next = next;
    p->prev = prev;
    return p;
}
dlist* dlist_create(void){
    dlist* p = (dlist*)malloc(sizeof(dlist));
    p->head = NULL;
    p->tail = NULL;
    p->size = 0;
    return p;
}

bool dlist_empty(dlist* list){ return list->size == 0; }
size_t dlist_size(dlist* list){ return list->size; }

void dlist_popfront(dlist* list){
    if(dlist_empty(list)) { printf("List is empty\n"); }
    else if(dlist_size(list) == 1){
        dnode* p = list->head;
        list->head = list->tail = NULL;
        free(p);
        --list->size;
     }
    else{
    dnode* p = list->head;
    list->head = list->head->next;
    list->head->prev = NULL;
    free(p);
    --list->size;
    }
}
void dlist_popback(dlist* list){
    if(dlist_empty(list)) { printf("List is empty\n"); }
    else if(dlist_size(list) == 1){ dlist_popfront(list); }
    else{
    dnode* p = list->tail;
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    free(p);
    --list->size;
    }
    // p = p->prev;
    // p->next = NULL;
    // free(list->tail);
    // list->tail = p;
    // --list->size;
}

void dlist_pushfront(dlist* list, int data){
    if(dlist_empty(list)){
        list->head = list->tail = dnode_create(data, NULL, NULL);// empty list
        ++list->size;
    }
    else{ 
    dnode *p = dnode_create(data, NULL , list->head); 
    list->head->prev = p;
    list->head = p;
    ++list->size;
    }
}
void dlist_pushback(dlist* list, int data){
    if(dlist_empty(list)){ 
        list->head = list->tail = dnode_create(data, NULL, NULL);// empty list
        ++list->size;
    }
    else{
    dnode *p = dnode_create(data, list->tail , NULL); 
    list->tail->next = p;
    list->tail = p;
    ++list->size;
    }
}

void dlist_clear(dlist* list){ 
    while(!dlist_empty(list)){ dlist_popfront(list); }
} 

void dlist_print(dlist* list, const char* msg){
    if(dlist_empty(list)) { printf("List is empty\n");}
    else{
    printf("%s\n", msg);
   dnode* p = list->head;
   while(p != NULL){
       printf("%11p <== %d (%p) ==> %p\n",p->prev , p->data, p, p->next);
       p = p->next;
    }
    }
}

int dlist_front(dlist* list){
    if(dlist_empty(list)) { printf("List is empty\n"); return 0;}
    return list->head->data;
}
int dlist_back(dlist* list){
    if(dlist_empty(list)) { printf("List is empty\n"); return 0;}
    return list->tail->data;
}

// void dlist_test(void); already exist in dlist_test.c