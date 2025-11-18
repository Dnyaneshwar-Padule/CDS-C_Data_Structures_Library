#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/doublylinkedlist.h"

doubly_list_node* doubly_list_insert(doubly_list_node* head, const void *data, size_t size){
    doubly_list_node* new_node = NEW_NODE();
    doubly_list_node* current = head;
    if(! new_node)
        return head;

    new_node->data = malloc(size);
    if(! new_node->data){
        free(new_node);
        return head;
    }

    memcpy(new_node->data, data, size);
    new_node->previous = NULL;
    new_node->next = NULL;

    if(! current){
        return new_node;
    }

    while(current->next)
        current = current->next;
    
    new_node->previous = current;
    current->next = new_node;
    return head;
}

doubly_list_node* doubly_list_insert_first(doubly_list_node* head, const void* data, size_t size){
    doubly_list_node* new_node = NEW_NODE();
    if(!new_node) return head;
    new_node->data = malloc(size);
    
    if(! new_node->data){
        free(new_node);
        return head;
    }

    memcpy(new_node->data, data, size);
    new_node->previous = NULL;
    new_node->next = head;
    if(head)head->previous = new_node;
    head = new_node;
    return head;
}

doubly_list_node* doubly_list_insert_last(doubly_list_node* head, const void *data, size_t size ){
    return doubly_list_insert(head, data, size);
}

doubly_list_node* doubly_list_insert_at(doubly_list_node* head, const void* data, size_t size, unsigned int index){
    if(index == 0 || index == 1){
        return doubly_list_insert_first(head, data, size);
    }

    doubly_list_node* current = head, *next = NULL;
    unsigned int i = 1;
    doubly_list_node* new_node = NEW_NODE();
    if(! new_node) return head;
    
    new_node->data = malloc(size);

    if(! new_node->data){
        free(new_node);
        return head;
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
        return head;
    }

    next = current->next;        // get address of next nodes
    current->next = new_node;   // attach new doubly_list_node 
    new_node->previous = current;  //set new doubly_list_node's previous to current
    new_node->next = next;        // set new doubly_list_node's next to remaining nodes
    if(next) next->previous = new_node;  // if next is a valid doubly_list_node, then make it's previous to the new doubly_list_node
    return head;
}

doubly_list_node* doubly_list_get_node(doubly_list_node* head, unsigned const int index){
    if( ! head || index <= 0 ) return NULL;

    doubly_list_node* current = head;
    unsigned int i = 1;

    while(current && i < index){
        ++i;
        current = current->next;
    }

    return current;
}

void* doubly_list_first(doubly_list_node* head){
    if(! head) return NULL;
    return head->data;
}

void* doubly_list_last(doubly_list_node *head){
    if(! head ) return NULL;
    doubly_list_node* current = head;
    while(current->next) current = current->next;
    return current->data;
}

void* doubly_list_get(doubly_list_node *head, unsigned const int index){
    doubly_list_node* doubly_list_node = doubly_list_get_node(head, index);
    if(! doubly_list_node) return NULL;
    return doubly_list_node->data;
}

int doubly_list_index_of(doubly_list_node* head, const void *data, int (*compare)(const void*, const void*)){
    if(!head ) return -1;

    doubly_list_node* current = head;
    unsigned int i = 1;

    while (current){
        if(compare(data, current->data) == 0)
            return i;
        ++i;
        current = current->next;
    }
    return -1;
}

int doubly_list_last_index_of(doubly_list_node* head, const void *data, int (*compare)(const void*, const void*)){
    if(! head ) return -1;

    doubly_list_node* current = head;
    int i = 1, last_index_of_target_node = -1;

    while (current){
        if(compare(data, current->data) == 0)
            last_index_of_target_node = i;
        ++i;
        current = current->next;
    }
    return last_index_of_target_node;
}

int doubly_list_contains(doubly_list_node* head, const void *data, int (*compare)(const void*, const void*)){
    if(! head ) return 0;

    doubly_list_node* current = head;
    unsigned int i = 1;

    while (current){
        if(compare(data, current->data) == 0)
            return 1;
        ++i;
        current = current->next;
    }
    return 0;
}

doubly_list_node* doubly_list_remove_first(doubly_list_node *head){
    doubly_list_node *current = head;

    if(! current)
        return NULL;
    
    head = head->next;
    free(current->data);  // data is also allocated on the heap
    free(current);
    if(head) head->previous = NULL; // update pointer
    return head; 
}

doubly_list_node* doubly_list_remove_last(doubly_list_node* head){
    if(! head ) return NULL; // empty list, return NULL
    doubly_list_node* current = head, *previous = NULL; 
    while(current->next) current = current->next; // go to the last doubly_list_node
    previous = current->previous;                // make previous's next null;
    free(current->data);
    free(current);
    if(previous) previous->next = NULL;
    if(! previous) return NULL; // previous is NULL, it means there was only one doubly_list_node 
    return head;
}

doubly_list_node* doubly_list_remove_at(doubly_list_node* head, unsigned const int index){
    if(! head) return NULL;
    if( index == 0 ) return head;
    if( index == 1) return doubly_list_remove_first(head);

    doubly_list_node *current = head, *previous = NULL;
    unsigned int i = 1;
    
    while(current && i < index){
        i++;
        current = current->next;
    }

    //Invalid index
    if(! current) return head;

    previous = current->previous;
    previous->next = current->next;
    if(current->next) current->next->previous = previous;
    free(current->data);
    free(current);
    return head;
}

doubly_list_node* doubly_list_remove_value(doubly_list_node* head, const void *value, int (*compare)(const void*, const void*)){
    if(! head) return NULL;

    doubly_list_node* current = head, *previous = NULL;

    if(compare(value, current->data) == 0)
        return doubly_list_remove_first(head);


    while(current){
        if(compare(value, current->data) == 0) break; // doubly_list_node found
        current = current->next;
    }

    //doubly_list_node not found
    if(! current) return head;

    previous = current->previous;
    previous->next = current->next;
    if(current->next) current->next->previous = previous;
    free(current->data);
    free(current);
    return head;
}

doubly_list_node* doubly_list_update(doubly_list_node* head, const void *old_data, const void *new_data, size_t size, int (*compare)(const void*, const void*) ){
    if( ! head) return NULL;

    doubly_list_node* current = head;
    void* new_copy = malloc(size);
    if(! new_copy) return head;
    memcpy(new_copy, new_data, size);

    while(current){
        if(compare(old_data, current->data) == 0){
            free(current->data);
            current->data = new_copy;
            return head;
        }
        current = current->next;
    }

    free(new_copy);
    return head;
}

doubly_list_node* doubly_list_reverse(doubly_list_node* head){
    doubly_list_node* current = head, *previous = NULL, *next = NULL;

    while(current){
        next = current->next;
        current->next = previous;
        current->previous = next;
        previous = current;
        current = next;
    }

    return previous;
}

doubly_list_node* doubly_list_clone(doubly_list_node* head, size_t size){
    if(! head) return NULL;

    doubly_list_node* new_head = NULL;
    doubly_list_node* current = head;

    while(current){
        new_head = doubly_list_insert_first(new_head, current->data, size);
        current = current->next;
    }

    return doubly_list_reverse(new_head);
}

doubly_list_node* doubly_list_append(doubly_list_node* head1, doubly_list_node* head2){
    if(! head2) return head1;
    if(! head1) return head2;

    doubly_list_node* current = head1;
    while(current->next) current = current->next;
    current->next = head2;
    head2->previous = current;
    return head1;
}

void doubly_list_clear(doubly_list_node * head){
    doubly_list_node *current = head;
    while(head){
        current = head;
        head = head->next;
        free(current->data);
        free(current);
    }
}

unsigned int doubly_list_length(doubly_list_node* head){
    unsigned int lengeth = 0;
    doubly_list_node* current = head;
    while(current){
        ++lengeth;
        current = current->next;
    }
    return lengeth;
}