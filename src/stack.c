#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/stack.h"


int stack_is_empty(stack_node *top){
    return top == BOTTOM;
}

stack_node* stack_push(stack_node* top, const void* data, size_t size){
    stack_node* new_node = NEW_NODE();    
    if(! new_node){
        fprintf(stderr, "stack_node is full !\n");
        return top;
    }

    new_node->data = malloc(size);
    if( !new_node->data ){
        fprintf(stderr, "Unable to allocate memory for data !\n");
        free(new_node);
        return top;
    }
    memcpy(new_node->data, data, size);
    new_node->next = NULL;
    new_node->previous = NULL;

    if(stack_is_empty(top)){
        top = new_node;
        return top;
    }

    // Adding new node at first
    new_node->next = top;
    top->previous = new_node;
    top = new_node;
    return top;
}

void* stack_pop(stack_node** top){
    if(stack_is_empty(*top)){
        return NULL;
    }

    stack_node* prev = *top;
    void *data = (*top)->data;
    (*top) = (*top)->next;
    if(*top) (*top)->previous = NULL;
    free(prev);
    return data;
}

void* stack_peek(stack_node* top){
    if(stack_is_empty(top)) return NULL;
    return top->data;
}

int stack_search(stack_node* top, const void* data, int (*compare)(const void*, const void*)){
    if(stack_is_empty(top)) return -1;

    int index_of_target_node = -1, index = 1;
    stack_node* traverser = top;

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

void stack_clear(stack_node** top){
     stack_node *current = *top;
    while(*top){
        current = *top;
        *top = (*top)->next;
        free(current->data);
        free(current);
    }
    *top = BOTTOM;
}

unsigned int stack_length(stack_node *top){
    unsigned int length = 0;

    stack_node *current = top;
    
    while (current){
        length++;
        current = current->next;
    }
    return length;
}
