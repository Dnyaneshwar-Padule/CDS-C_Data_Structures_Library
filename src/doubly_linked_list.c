#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/doubly_linked_list.h"

doubly_linked_list* doubly_linked_list_init(){
    doubly_linked_list *dll = (doubly_linked_list*)malloc(sizeof(doubly_linked_list));
    if(! dll) return NULL;
    dll->head = NULL;
    return dll;
}

doubly_linked_list* doubly_list_insert(doubly_linked_list* d_linked_list, const void *data, size_t size){
    if(! d_linked_list) return NULL;
    doubly_list_node* new_node = NEW_NODE();
    doubly_list_node* current = d_linked_list->head;
    if(! new_node)
        return d_linked_list;

    new_node->data = malloc(size);
    if(! new_node->data){
        free(new_node);
        return d_linked_list;
    }

    memcpy(new_node->data, data, size);
    new_node->previous = NULL;
    new_node->next = NULL;

    if(! current){
        d_linked_list->head = new_node;
        return d_linked_list;
    }

    while(current->next)
        current = current->next;
    
    new_node->previous = current;
    current->next = new_node;
    return d_linked_list;
}

doubly_linked_list* doubly_list_insert_first(doubly_linked_list* d_linked_list, const void* data, size_t size){
    if(! d_linked_list) return NULL;
    doubly_list_node* new_node = NEW_NODE();
    if(!new_node) return d_linked_list;
    new_node->data = malloc(size);
    
    if(! new_node->data){
        free(new_node);
        return d_linked_list;
    }

    memcpy(new_node->data, data, size);
    new_node->previous = NULL;
    new_node->next = d_linked_list->head;
    if(d_linked_list->head) d_linked_list->head->previous = new_node;
    d_linked_list->head = new_node;
    return d_linked_list;
}

doubly_linked_list* doubly_list_insert_last(doubly_linked_list* d_linked_list, const void *data, size_t size ){
    return doubly_list_insert(d_linked_list, data, size);
}

doubly_linked_list* doubly_list_insert_at(doubly_linked_list* d_linked_list, const void* data, size_t size, unsigned int index){
    if(! d_linked_list) return NULL;
    if(index == 0 || index == 1){
        return doubly_list_insert_first(d_linked_list, data, size);
    }

    doubly_list_node* current = d_linked_list->head, *next = NULL;
    unsigned int i = 1;
    doubly_list_node* new_node = NEW_NODE();
    if(! new_node) return d_linked_list;
    
    new_node->data = malloc(size);

    if(! new_node->data){
        free(new_node);
        return d_linked_list;
    }

    memcpy(new_node->data, data, size);
    new_node->next = NULL;
    new_node->previous = NULL;

    while(current && i < index-1){
        current = current->next;
        i++;
    }

    //Invalid index
    if(!current){
        free(new_node->data);
        free(new_node);
        return d_linked_list;
    }

    next = current->next;        // get address of next nodes
    current->next = new_node;   // attach new doubly_list_node 
    new_node->previous = current;  //set new doubly_list_node's previous to current
    new_node->next = next;        // set new doubly_list_node's next to remaining nodes
    if(next) next->previous = new_node;  // if next is a valid doubly_list_node, then make it's previous to the new doubly_list_node
    return d_linked_list;
}

doubly_list_node* doubly_list_get_node(doubly_linked_list* d_linked_list, unsigned const int index){
    if(! d_linked_list) return NULL;
    if( ! d_linked_list->head || index <= 0 ) return NULL;

    doubly_list_node* current = d_linked_list->head;
    unsigned int i = 1;

    while(current && i < index){
        ++i;
        current = current->next;
    }

    return current;
}

void* doubly_list_first(doubly_linked_list* d_linked_list){
    if(! d_linked_list) return NULL;
    if(! d_linked_list) return NULL;
    return d_linked_list->head->data;
}

void* doubly_list_last(doubly_linked_list *d_linked_list){
    if(! d_linked_list) return NULL;
    if(! d_linked_list->head ) return NULL;
    doubly_list_node* current = d_linked_list->head;
    while(current->next) current = current->next;
    return current->data;
}

void* doubly_list_get(doubly_linked_list *d_linked_list, unsigned const int index){
    if(! d_linked_list) return NULL;
    doubly_list_node* doubly_list_node = doubly_list_get_node(d_linked_list, index);
    if(! doubly_list_node) return NULL;
    return doubly_list_node->data;
}

int doubly_list_index_of(doubly_linked_list* d_linked_list, const void *data, int (*compare)(const void*, const void*)){
    if(! d_linked_list) return -1;
    if(! d_linked_list->head ) return -1;

    doubly_list_node* current = d_linked_list->head;
    unsigned int i = 1;

    while (current){
        if(compare(data, current->data) == 0)
            return i;
        ++i;
        current = current->next;
    }
    return -1;
}

int doubly_list_last_index_of(doubly_linked_list* d_linked_list, const void *data, int (*compare)(const void*, const void*)){
    if(! d_linked_list) return -1;
    if(! d_linked_list->head ) return -1;

    doubly_list_node* current = d_linked_list->head;
    int i = 1, last_index_of_target_node = -1;

    while (current){
        if(compare(data, current->data) == 0)
            last_index_of_target_node = i;
        ++i;
        current = current->next;
    }
    return last_index_of_target_node;
}

int doubly_list_contains(doubly_linked_list* d_linked_list, const void *data, int (*compare)(const void*, const void*)){
    if(! d_linked_list) return 0;
    if(! d_linked_list->head ) return 0;

    doubly_list_node* current = d_linked_list->head;
    unsigned int i = 1;

    while (current){
        if(compare(data, current->data) == 0)
            return 1;
        ++i;
        current = current->next;
    }
    return 0;
}

doubly_linked_list* doubly_list_remove_first(doubly_linked_list *d_linked_list){
    if(! d_linked_list) return NULL;
    doubly_list_node *current = d_linked_list->head;

    if(! current)
        return NULL;
    
    d_linked_list->head = d_linked_list->head->next;
    free(current->data);  // data is also allocated on the heap
    free(current);
    if(d_linked_list->head) d_linked_list->head->previous = NULL; // update pointer
    return d_linked_list; 
}

doubly_linked_list* doubly_list_remove_last(doubly_linked_list* d_linked_list){
    if(! d_linked_list) return NULL;
    if(! d_linked_list->head ) return NULL; // empty list, return NULL
    doubly_list_node* current = d_linked_list->head, *previous = NULL; 
    while(current->next) current = current->next; // go to the last doubly_list_node
    previous = current->previous;                // make previous's next null;
    free(current->data);
    free(current);
    if(previous) previous->next = NULL;
    if(! previous) return NULL; // previous is NULL, it means there was only one doubly_list_node 
    return d_linked_list;
}

doubly_linked_list* doubly_list_remove_at(doubly_linked_list* d_linked_list, unsigned const int index){
    if(! d_linked_list) return NULL;
    if(! d_linked_list->head) return NULL;
    if( index == 0 ) return d_linked_list;
    if( index == 1) return doubly_list_remove_first(d_linked_list);

    doubly_list_node *current = d_linked_list->head, *previous = NULL;
    unsigned int i = 1;
    
    while(current && i < index){
        i++;
        current = current->next;
    }

    //Invalid index
    if(! current) return d_linked_list;

    previous = current->previous;
    previous->next = current->next;
    if(current->next) current->next->previous = previous;
    free(current->data);
    free(current);
    return d_linked_list;
}

doubly_linked_list* doubly_list_remove_value(doubly_linked_list* d_linked_list, const void *value, int (*compare)(const void*, const void*)){
    if(! d_linked_list) return NULL;
    if(! d_linked_list->head) return NULL;

    doubly_list_node* current = d_linked_list->head, *previous = NULL;

    if(compare(value, current->data) == 0)
        return doubly_list_remove_first(d_linked_list);


    while(current){
        if(compare(value, current->data) == 0) break; // doubly_list_node found
        current = current->next;
    }

    //doubly_list_node not found
    if(! current) return d_linked_list;

    previous = current->previous;
    previous->next = current->next;
    if(current->next) current->next->previous = previous;
    free(current->data);
    free(current);
    return d_linked_list;
}

doubly_linked_list* doubly_list_update(
    doubly_linked_list* d_linked_list, 
    const void *old_data, 
    const void *new_data, 
    size_t size, 
    int (*compare)(const void*, const void*) 
){
    if(! d_linked_list) return NULL;
    if( ! d_linked_list->head) return NULL;

    doubly_list_node* current = d_linked_list->head;
    void* new_copy = malloc(size);
    if(! new_copy) return d_linked_list;
    memcpy(new_copy, new_data, size);

    while(current){
        if(compare(old_data, current->data) == 0){
            free(current->data);
            current->data = new_copy;
            return d_linked_list;
        }
        current = current->next;
    }

    free(new_copy);
    return d_linked_list;
}

doubly_linked_list* doubly_list_reverse(doubly_linked_list* d_linked_list){
    if(! d_linked_list) return NULL;
    doubly_list_node* current = d_linked_list->head, *previous = NULL, *next = NULL;

    while(current){
        next = current->next;
        current->next = previous;
        current->previous = next;
        previous = current;
        current = next;
    }
    d_linked_list->head = previous;    
    return d_linked_list;
}

doubly_linked_list* doubly_list_clone(doubly_linked_list *dest, doubly_linked_list* src, size_t size){
    if(! src || ! dest) return NULL;
    if(! src->head) return NULL;

    doubly_list_node* current = src->head;

    while(current){
        doubly_list_insert_first(dest, current->data, size);
        current = current->next;
    }

    return doubly_list_reverse(dest);
}

doubly_linked_list* doubly_list_append(doubly_linked_list* d_linked_list1, doubly_linked_list* d_linked_list2){
    if(! d_linked_list1 || ! d_linked_list2) return NULL;
    if(! d_linked_list2) return d_linked_list1;
    if(! d_linked_list1) return d_linked_list2;

    doubly_list_node* current = d_linked_list1->head;
    while(current->next) current = current->next;
    current->next = d_linked_list2->head;
    d_linked_list2->head->previous = current;
    return d_linked_list1;
}

void doubly_list_clear(doubly_linked_list ** d_linked_list){
    if(! d_linked_list || ! (*d_linked_list)) return;
    doubly_list_node *current = (*d_linked_list)->head;
    while((*d_linked_list)->head){
        current = (*d_linked_list)->head;
        (*d_linked_list)->head = (*d_linked_list)->head->next;
        free(current->data);
        free(current);
    }
    free(*d_linked_list);
    *d_linked_list = NULL;
}

unsigned int doubly_list_length(doubly_linked_list* d_linked_list){
    if(! d_linked_list) return 0;
    unsigned int lengeth = 0;
    doubly_list_node* current = d_linked_list->head;
    while(current){
        ++lengeth;
        current = current->next;
    }
    return lengeth;
}