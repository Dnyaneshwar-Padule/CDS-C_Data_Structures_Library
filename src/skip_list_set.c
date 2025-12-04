#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include "../include/skip_list_set.h"

skip_list_set* skip_list_set_init(){
    // Seeding the random number generator
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }

    
    skip_list_set *list_set = (skip_list_set*)malloc(sizeof(skip_list_set)); 
    if(! list_set){
        fprintf(stderr, "Unable to allocate memory for skip list set !\n");
        return NULL;
    }
    
    list_set->size = 0; // initial size of set
    list_set->p = 0.5;  // coin flip
    
    list_set->head = NEW_CLEAR_NODE;
    if(! list_set->head){
        free(list_set);
        fprintf(stderr, "Unable to allocate memory for skip list set !\n");
        return NULL;
    }
    return list_set;
}


int random_level(skip_list_set *list_set) {
    int level = 0;
    while ((float)rand() / RAND_MAX < list_set->p && level <= list_set->head->level) {
        level++;
    }
    return level;
}

skip_list_set_node* skip_list_set_create_new_node(long level, const void * key, size_t size, skip_list_set_node *next, skip_list_set_node *down){
    skip_list_set_node *node = NEWNODE;
    node->level = level;
    node->down = down;
    node->next = next;
    
    if(key && size){
        node->key = malloc(size);
        memcpy(node->key, key, size);
    }
    return node;
}


int skip_list_set_add(skip_list_set *list_set, const void *key, size_t size, int (*compare)(const void*, const void*)){
    if(! list_set || ! key)
        return 0;

    int level = random_level(list_set);

    if(level > list_set->head->level){
       list_set->head = skip_list_set_create_new_node(level, NULL, 0, NULL, list_set->head);
    }

    skip_list_set_node *current = list_set->head, *last = NULL;

    while (current){
        if(! current->next || compare(current->next->key, key) > 0){
            if(level >= current->level){
                skip_list_set_node *node = skip_list_set_create_new_node(current->level, key, size, current->next, NULL);
                if(last)
                    last->down = node;
        
                current->next = node;
                last = node;
            }
            current = current->down;
            continue;
        }
        else if (compare(current->next->key, key) == 0){
            if(last) last->down = current->next;   // very important.....
            return 0;
        }
        current = current->next;
    }
    list_set->size++;
    return 1;
}


int skip_list_set_contains(skip_list_set *list_set, const void* key, int (*compare)(const void*, const void*)){
    if(! list_set || ! key)
        return 0;

    skip_list_set_node *current = list_set->head;

    while (current){
        if(! current->next || compare(current->next->key, key) > 0){
            current = current->down;
            continue;
        }
        else if (compare(current->next->key, key) == 0){
            return 1;
        }
        current = current->next;
    }
    return 0;
}


int skip_list_set_remove(skip_list_set *list_set, const void *key, int (*compare)(const void*, const void*)){
    if(! list_set || ! key)
        return 0;

    int is_found = 0;
    skip_list_set_node *current = list_set->head, *temp = NULL;

    while (current){
        if(! current->next || compare(current->next->key, key) >= 0){
            if(current->next && compare(current->next->key, key) == 0){
                is_found = 1;
                temp = current->next;
                current->next = current->next->next;
                free(temp->key);
                free(temp);
            }
            current = current->down;
            continue;
        }
        current = current->next;
    }

    if(is_found) 
        list_set->size--;
    return is_found;
}

unsigned long skip_list_set_size(skip_list_set *list_set ){
    if(! list_set )
        return 0;
    return list_set->size;
}

void skip_list_set_clear(skip_list_set **list_set){
    if(! list_set || ! *list_set) return;
    
    skip_list_set_node *current = (*list_set)->head, *next = NULL, *down = NULL;

    while (current){
        down = current->down;
        while (current){
            next = current->next;
            if(current->key)
                free(current->key);
            free(current);
            current = next;
        }
        current = down;
    }
    
    free(*list_set);
    *list_set = NULL;
}