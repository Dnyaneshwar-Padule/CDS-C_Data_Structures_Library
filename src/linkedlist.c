#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/linkedlist.h"

list_node* list_insert(list_node* head, const void *data, size_t size)
{
    list_node *current = head;
    list_node *new_node = NEWNODE();
    if(! new_node){
        fprintf(stderr, "Unable to allocate memory for new list_node!\n");
        return head;
    }
    
    new_node->data = malloc(size); //allocating space for data
    if(! new_node->data){
        fprintf(stderr, "Unable to allocate memory for data!\n");
        free(new_node);
        return head;
    }
    
    memcpy(new_node->data, data, size); // copying data 
    new_node->next = NULL;

    // linked list is empty
    if(! current){
        return new_node;
    }
    
    // traverse till last list_node
    while( current->next )
        current = current->next;

    // attach new list_node
    current->next = new_node;
    return head;
}

list_node* list_insert_first(list_node* head, const void* data, size_t size){
    list_node* new_node = NEWNODE();
    if( ! new_node ){
        fprintf(stderr, "Unable to allocate memory for new list_node!\n");
        return head;
    }
    
    new_node->data = malloc(size);
    if( ! new_node->data ){
        fprintf(stderr, "Unable to allocate memory for data !\n");
        free(new_node);
        return head;
    }

    memcpy(new_node->data, data, size); // copy data
    new_node->next = head;
    head = new_node;
    return head;
}

list_node* list_insert_last(list_node* head, const void *data, size_t size ){
    return list_insert(head, data, size);
}

void* list_first(list_node* head){
    if(! head)
        return NULL;

    return head->data;
}

void* list_last(list_node *head){
    list_node *current = head;

    if(! current)
        return NULL;
    
    // traverse till last list_node
    while( current->next )
        current = current->next;
    return current->data;
}

unsigned int list_length(list_node* head){
    unsigned int length = 0;
    list_node* current = head;
    while(current){
        current = current->next;
        length++;
    }
    return length;
}

list_node* list_remove_first(list_node *head){
    list_node *current = head;

    if(! current)
        return NULL;
    
    head = head->next;
    free(current->data);  // data is also allocated on the heap
    free(current);
    return head;
}

list_node* list_remove_last(list_node* head){
    list_node* current = head, *previous = NULL;
    
    if(! current)
        return NULL;
    
    while( current->next ){
        previous = current;
        current = current->next;
    }

    free(current->data);
    free(current);

    // there was only one list_node
    if( ! previous )
        return NULL;
    
    previous->next = NULL;
    return head;
}

list_node* list_remove_at(list_node* head, unsigned const int index){
    list_node* current = head, *node_to_delete = NULL;
    unsigned int i = 1;
    if(! current)
        return NULL;
 
    if(index == 0) 
        return head;
        
    if(index == 1){
        current = current->next;
        free(head->data);
        free(head);
        head = current;
        return head;
    }

    // traverse till last list_node or till index - 1
    while(current && i < index - 1){
        current = current->next;
        i++;
    }

    //Invalid index, return
    if(! current || ! current->next)
        return head;
    
    node_to_delete = current->next;
    current->next = node_to_delete->next; // attach remaining nodes to the previous list_node of list_node to delete
    
    free(node_to_delete->data);
    free(node_to_delete);

    return head;
}

void* list_get(list_node *head, unsigned const int index){
    if( ! head || index <= 0 )
        return NULL;
    
    list_node * current = head;
    unsigned int i = 1; 
    
    while(current && i < index){
        current = current->next;
        ++i;
    }

    // Invalid index
    if( ! current )
        return NULL;

    return current->data;
}

list_node* list_get_node(list_node* head, unsigned const int index){
    if( ! head || index <= 0 )
        return NULL;
    
    list_node * current = head;
    unsigned int i = 1; 
    
    while(current && i < index){
        current = current->next;
        ++i;
    }

    return current;
}

list_node* list_insert_at(list_node* head, const void* data, size_t size, unsigned int index){
    if(index <= 1)
        return list_insert_first(head, data, size);

    list_node* current = head;
    list_node* new_node = NEWNODE();
    unsigned int i = 1;

    if( ! new_node ) return head;
    new_node->data = malloc(size);
    if( !new_node->data ){
        free(new_node);
        return head;
    }
    memcpy(new_node->data, data, size);
    new_node->next = NULL;

    while(current && i < index - 1){
        current = current->next;
        ++i;
    }

    // Invalid index
    if(! current){
        free(new_node->data);
        free(new_node);
        return head;
    }

    new_node->next = current->next;
    current->next = new_node;
    return head;
}

int list_contains(list_node* head, const void *data, int (*compare)(const void*, const void*)){
    list_node* current = head;

    while(current){
        // compare function should work like strcmp -1 for smaller, 0 for equal, 1 for greater
        if( compare(data, current->data) == 0){
            return 1; // return true
        }
        current = current->next;
    }

    return 0;
}

list_node* list_remove_value(list_node* head, const void *value, int (*compare)(const void*, const void*)){
    if(! head) return NULL;

    list_node* current = head, *previous = NULL;

    if(compare(value, current->data) == 0)
        return list_remove_first(head);

    previous = current;
    current = current->next;

    while( current ){
        if(compare(value, current->data) == 0){
            previous->next = current->next;
            free(current->data);
            free(current);
            return head;
        }
        previous = current;
        current = current->next;
    }

    return head;
}

list_node* list_update(list_node* head, const void *old_data, const void *new_data, size_t size, int (*compare)(const void*, const void*) ){
    if(! head) return NULL;

    list_node* current = head;
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

int list_index_of(list_node* head, const void *data, int (*compare)(const void*, const void*)){
    if(! head) return -1;

    int index = 1;
    list_node* current = head;

    while(current){
        if(compare(data, current->data) == 0)
            return index;
        index++;
        current = current->next;
    }

    return -1;
}

list_node* list_reverse(list_node* head){
    if(! head) return NULL;
    list_node *current = head, *previous = NULL, *next = NULL;
    while(current){
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    return previous;
}

void list_clear(list_node * head){
    list_node* current = head;
    while(head){
        current = head;
        head = head->next;
        free(current->data);
        free(current);
    }
}

list_node* list_clone(list_node* head, size_t size){
    if(! head ) return NULL;

    list_node* new_head = NULL, *current = head;

    while(current){
        new_head = list_insert_first(new_head, current->data, size);
        current = current->next;
    }

    return list_reverse(new_head);
}

list_node* list_append(list_node* head1, list_node* head2){
    if(! head2) return head1;
    if(! head1) return head2;

    list_node* current = head1;
    while(current->next)
        current = current->next;
    current->next = head2;
    return head1;
}

int list_last_index_of(list_node* head, const void *data, int (*compare)(const void*, const void*)){
    if(! head) return -1;

    int index = 1, target_node_last_index = -1;
    list_node* current = head;

    while(current){
        if(compare(data, current->data) == 0)
            target_node_last_index = index;
        index++;
        current = current->next;
    }

    return target_node_last_index;
}
