#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/stack.h"

void init(stack * s){
    if(s)s->top = NULL;
}

int stack_is_empty(stack *s){
    if(! s) return 0;
    return s->top == BOTTOM;
}

stack* stack_push(stack* s, const void* data, size_t size){
    if(! s ) return NULL;
    stack_node* new_node = NEW_NODE();    
    if(! new_node){
        fprintf(stderr, "stack_node is full !\n");
        return s;
    }

    new_node->data = malloc(size);
    if( !new_node->data ){
        fprintf(stderr, "Unable to allocate memory for data !\n");
        free(new_node);
        return s;
    }
    memcpy(new_node->data, data, size);
    new_node->next = NULL;
    new_node->previous = NULL;

    if(stack_is_empty(s)){
        s->top = new_node;
        return s;
    }

    // Adding new node at first
    new_node->next = s->top;
    s->top->previous = new_node;
    s->top = new_node;
    return s;
}

void* stack_pop(stack* s){
    if(! s ) return NULL;
    if(stack_is_empty(s)){
        return NULL;
    }

    stack_node* prev = s->top;
    void *data = (s->top)->data;
    (s->top) = (s->top)->next;
    if(s->top) (s->top)->previous = NULL;
    free(prev);
    return data;
}

void* stack_peek(stack* s){
    if(! s) return NULL;
    if(stack_is_empty(s)) return NULL;
    return s->top->data;
}

int stack_search(stack* s, const void* data, int (*compare)(const void*, const void*)){
    if(! s) return -1;
    if(stack_is_empty(s)) return -1;

    int index_of_target_node = -1, index = 1;
    stack_node* traverser = s->top;

    while(traverser){
        if( compare(data, traverser->data) == 0 ){
            index_of_target_node = index;
            break;
        }
        ++index;
        traverser = traverser->next;
    }

    return index_of_target_node ;
}

void stack_clear(stack* s){
    if(! s) return;
    stack_node *current = s->top;
    while(s->top){
        current = s->top;
        s->top = s->top->next;
        free(current->data);
        free(current);
    }
    init(s);
}

unsigned int stack_length(stack *s){
    unsigned int length = 0;

    stack_node *current = s->top;
    
    while (current){
        length++;
        current = current->next;
    }
    return length;
}
