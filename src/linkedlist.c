#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/linkedlist.h"

linked_list* list_init(){
    linked_list *l_list = (linked_list*)malloc(sizeof(linked_list));
    if(! l_list) return NULL; 
    l_list->head = NULL;
    return l_list;
}

linked_list* list_insert(linked_list* l_list, const void *data, size_t size)
{
    if(! l_list) return NULL;
    list_node *current = l_list->head;
    list_node *new_node = NEWNODE();
    if(! new_node){
        fprintf(stderr, "Unable to allocate memory for new list_node!\n");
        return l_list;
    }
    
    new_node->data = malloc(size); //allocating space for data
    if(! new_node->data){
        fprintf(stderr, "Unable to allocate memory for data!\n");
        free(new_node);
        l_list->head = new_node;
        return l_list;
    }
    
    memcpy(new_node->data, data, size); // copying data 
    new_node->next = NULL;

    // linked list is empty
    if(! current){
        l_list->head = new_node;
        return l_list;
    }
    
    // traverse till last list_node
    while( current->next )
        current = current->next;

    // attach new list_node
    current->next = new_node;
    return l_list;
}

linked_list* list_insert_first(linked_list* l_list, const void* data, size_t size){
    if(! l_list) return NULL;
    list_node* new_node = NEWNODE();
    if( ! new_node ){
        fprintf(stderr, "Unable to allocate memory for new list_node!\n");
        return l_list;
    }
    
    new_node->data = malloc(size);
    if( ! new_node->data ){
        fprintf(stderr, "Unable to allocate memory for data !\n");
        free(new_node);
        return l_list;
    }

    memcpy(new_node->data, data, size); // copy data
    new_node->next = l_list->head;
    l_list->head = new_node;
    return l_list;
}

linked_list* list_insert_last(linked_list* l_list, const void *data, size_t size ){
    return list_insert(l_list, data, size);
}

void* list_first(linked_list* l_list){
    if(! l_list) return NULL;
    else if(! l_list->head)
        return NULL;

    return l_list->head->data;
}

void* list_last(linked_list *l_list){
    if(! l_list) return NULL;
    list_node *current = l_list->head;

    if(! current)
        return NULL;
    
    // traverse till last list_node
    while( current->next )
        current = current->next;
    return current->data;
}

unsigned int list_length(linked_list* l_list){
    if(! l_list) return 0;
    unsigned int length = 0;
    list_node* current = l_list->head;
    while(current){
        current = current->next;
        length++;
    }
    return length;
}

linked_list* list_remove_first(linked_list *l_list){
    if(! l_list) return NULL;
    list_node *current = l_list->head;

    if(! current)
        return NULL;
    
    l_list->head = l_list->head->next;
    free(current->data);  // data is also allocated on the heap
    free(current);
    return l_list;
}

linked_list* list_remove_last(linked_list* l_list){
    if(! l_list) return NULL;
    list_node* current = l_list->head, *previous = NULL;
    
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
    return l_list;
}

linked_list* list_remove_at(linked_list* l_list, unsigned const int index){
    if(! l_list) return NULL;
    list_node* current = l_list->head, *node_to_delete = NULL;
    unsigned int i = 1;
    if(! current)
        return NULL;
 
    if(index == 0) 
        return l_list;
        
    if(index == 1){
        current = current->next;
        free(l_list->head->data);
        free(l_list->head);
        l_list->head = current;
        return l_list;
    }

    // traverse till last list_node or till index - 1
    while(current && i < index - 1){
        current = current->next;
        i++;
    }

    //Invalid index, return
    if(! current || ! current->next)
        return l_list;
    
    node_to_delete = current->next;
    current->next = node_to_delete->next; // attach remaining nodes to the previous list_node of list_node to delete
    
    free(node_to_delete->data);
    free(node_to_delete);

    return l_list;
}

void* list_get(linked_list *l_list, unsigned const int index){
    if(! l_list) return NULL;
    if( ! l_list->head || index <= 0 )
        return NULL;
    
    list_node * current = l_list->head;
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

list_node* list_get_node(linked_list* l_list, unsigned const int index){
    if(! l_list) return NULL;
    else if( ! l_list->head || index <= 0 )
        return NULL;
    
    list_node * current = l_list->head;
    unsigned int i = 1; 
    
    while(current && i < index){
        current = current->next;
        ++i;
    }

    return current;
}

linked_list* list_insert_at(linked_list* l_list, const void* data, size_t size, unsigned int index){
    if(! l_list) return NULL;
    else if(index <= 1)
        return list_insert_first(l_list, data, size);

    list_node* current = l_list->head;
    list_node* new_node = NEWNODE();
    unsigned int i = 1;

    if( ! new_node ) return l_list;
    new_node->data = malloc(size);
    if( !new_node->data ){
        free(new_node);
        return l_list;
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
        return l_list;
    }

    new_node->next = current->next;
    current->next = new_node;
    return l_list;
}

int list_contains(linked_list* l_list, const void *data, int (*compare)(const void*, const void*)){
    if(! l_list) return 0;
    list_node* current = l_list->head;

    while(current){
        // compare function should work like strcmp -1 for smaller, 0 for equal, 1 for greater
        if( compare(data, current->data) == 0){
            return 1; // return true
        }
        current = current->next;
    }

    return 0;
}

linked_list* list_remove_value(linked_list* l_list, const void *value, int (*compare)(const void*, const void*)){
    if(! l_list) return NULL;
    if(! l_list->head) return NULL;

    list_node* current = l_list->head, *previous = NULL;

    if(compare(value, current->data) == 0)
        return list_remove_first(l_list);

    previous = current;
    current = current->next;

    while( current ){
        if(compare(value, current->data) == 0){
            previous->next = current->next;
            free(current->data);
            free(current);
            return l_list;
        }
        previous = current;
        current = current->next;
    }

    return l_list;
}

linked_list* list_update(linked_list* l_list, const void *old_data, const void *new_data, size_t size, int (*compare)(const void*, const void*) ){
    if(! l_list) return NULL;
    if(! l_list->head) return NULL;

    list_node* current = l_list->head;
    void* new_copy = malloc(size);
    if(! new_copy) return l_list;
    memcpy(new_copy, new_data, size);

    while(current){
        if(compare(old_data, current->data) == 0){
            free(current->data);
            current->data = new_copy;
            return l_list;
        }
        current = current->next;
    }

    free(new_copy);
    return l_list;
}

int list_index_of(linked_list* l_list, const void *data, int (*compare)(const void*, const void*)){
    if(! l_list) return -1;
    if(! l_list->head) return -1;

    int index = 1;
    list_node* current = l_list->head;

    while(current){
        if(compare(data, current->data) == 0)
            return index;
        index++;
        current = current->next;
    }

    return -1;
}

linked_list* list_reverse(linked_list* l_list){
    if(! l_list) return NULL;
    if(! l_list->head) return NULL;
    list_node *current = l_list->head, *previous = NULL, *next = NULL;
    while(current){
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    l_list->head = previous;
    return l_list;
}

void list_clear(linked_list * l_list){
    if(! l_list) return;
    list_node* current = l_list->head;
    while(l_list->head){
        current = l_list->head;
        l_list->head = l_list->head->next;
        free(current->data);
        free(current);
    }
    free(l_list);
}

linked_list* list_clone(linked_list* dest, linked_list* src, size_t size){
    if(! src) return NULL;
    if(! dest) return NULL;
    if(! src->head ) return NULL;

    dest->head = NULL; 
    list_node *current = src->head;

    while(current){
        list_insert_first(dest, current->data, size);
        current = current->next;
    }

    return list_reverse(dest);
}

linked_list* list_append(linked_list* l_list1, linked_list* l_list2){
    if(! l_list1 || !l_list2) return NULL;
    if(! l_list2->head) return l_list1;
    if(! l_list1->head) return l_list2;

    list_node* current = l_list1->head;
    while(current->next)
        current = current->next;
    current->next = l_list2->head;
    return l_list1;
}

int list_last_index_of(linked_list* l_list, const void *data, int (*compare)(const void*, const void*)){
    if(! l_list) return -1;
    if(! l_list->head) return -1;

    int index = 1, target_node_last_index = -1;
    list_node* current = l_list->head;

    while(current){
        if(compare(data, current->data) == 0)
            target_node_last_index = index;
        index++;
        current = current->next;
    }

    return target_node_last_index;
}
