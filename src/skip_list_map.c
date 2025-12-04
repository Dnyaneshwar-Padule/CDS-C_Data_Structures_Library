#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "../include/skip_list_map.h"

skip_list_map *skip_list_map_init(){
    //seeding random number generator
    static int seeded = 0;
    if(!seeded){
        srand(time(NULL));
        seeded = 1;
    }
    
    skip_list_map *ordered_map = (skip_list_map*)malloc(sizeof(skip_list_map));
    
    if(!ordered_map)
        return NULL;

    // create a dummy head
    ordered_map->head = skip_list_map_create_new_node(0, NULL, 0, NULL, 0, NULL, NULL);
    
    //if unable to create dummy node, free ordered_map, and return NULL
    if(! ordered_map->head){
        free(ordered_map);
        return NULL;
    }

    ordered_map->p = 0.5;  // coin flip probability
    ordered_map->size = 0; // initial size
    return ordered_map;
}


skip_list_map_node* skip_list_map_create_new_node(
    unsigned int level, 
    const void *key,
    size_t key_size,
    const void *value,
    size_t value_size,
    skip_list_map_node *next,
    skip_list_map_node *down
){
    skip_list_map_node *node = NEWNODE;
    
    if(!node)
        return NULL;

    if(key && key_size){
        node->key = malloc(key_size);
        memcpy(node->key, key, key_size);
        if(! node->key){
            free(node);
            return NULL;
        }
    }

    if(value && value_size){
        node->value = malloc(value_size);
        memcpy(node->value, value, value_size);
        if(! value){
            free(node->key);
            free(node);
            return NULL;
        }
    }

    node->level = level;
    node->next = next;
    node->down = down;

    return node;
}


int skip_list_map_random_level(skip_list_map *ordered_map){
    int level = 0;
    while ((float)rand() / RAND_MAX < ordered_map->p && level <= ordered_map->head->level) {
        level++;
    }
    return level;
}



int skip_list_map_put(
    skip_list_map *ordered_map,
    const void *key,
    size_t key_size,
    const void *value,
    size_t value_size,
    int (*compare)(const void*, const void*)
)
{
    if(! ordered_map || ! key) 
        return 0;

    int level =  skip_list_map_random_level(ordered_map);

    if(level > ordered_map->head->level){
        skip_list_map_node *new_head = skip_list_map_create_new_node(level, NULL, 0, NULL, 0, NULL, ordered_map->head); 
        if(!new_head) return 0;
        ordered_map->head = new_head;
    }

    skip_list_map_node *current = ordered_map->head, *last = NULL;

    while(current){
        if(! current->next || compare(current->next->key, key) > 0){
            if(level >= current->level){
                skip_list_map_node *new_node = skip_list_map_create_new_node(current->level, key, key_size, value, value_size, current->next, NULL);
                if(last)
                    last->down = new_node;
                current->next = new_node;
                last = new_node;
            }
            current = current->down;
            continue;
        }
        else if(compare(current->next->key, key) == 0){
            if(last)
                last->down = current->next;

            // update value
            free(current->next->value);
            current->next->value = malloc(value_size);
            memcpy(current->next->value, value, value_size);
            return 1;
        }
        current = current->next;
    }

    ordered_map->size++;
    return 1;
}


int skip_list_map_contains(skip_list_map *ordered_map, const void* key, int (*compare)(const void*, const void*)){
    if(! ordered_map || ! key) return 0;

    skip_list_map_node *current = ordered_map->head;

    while (current){
        if(! current->next || compare(current->next->key, key) > 0){
            current = current->down;
            continue;
        }
        else if(compare(current->next->key, key) == 0){
            return 1;
        }
        current = current->next;
    }

    return 0;
}


void* skip_list_map_get(skip_list_map *ordered_map, const void *key, int (*compare)(const void*, const void*)){
    if(! ordered_map || ! key) return NULL;

    skip_list_map_node *current = ordered_map->head;

    while (current){
        if(! current->next || compare(current->next->key, key) > 0){
            current = current->down;
            continue;
        }
        else if(compare(current->next->key, key) == 0){
            return current->next->value;
        }
        current = current->next;
    }

    return NULL;
}


int skip_list_map_remove( skip_list_map *orderd_map, const void *key, int (*compare)(const void*, const void*)){
    if(! orderd_map || !key) 
        return 0;
    
    skip_list_map_node *current = orderd_map->head, *temp = NULL;
    int is_removed = 0;

    while(current){
        if(! current->next || compare(current->next->key, key) >= 0){
            if(current->next && compare(current->next->key, key) == 0){
                is_removed = 1;
                temp = current->next;
                current->next =  current->next->next;
                free(temp->key);
                free(temp->value);
                free(temp);
            }
            current = current->down;
            continue;
        }
        current = current->next;
    }

    if(is_removed)
        orderd_map->size--;

    return is_removed;    
}


void skip_list_map_clear(skip_list_map **orderd_map){
    if(! orderd_map || ! *orderd_map)
        return;

    skip_list_map *map = *orderd_map;
    skip_list_map_node *current = map->head, *next = NULL, *down = NULL;

    while(current){
        down = current->down;
        while(current){
            next = current->next;
            if(current->key)
                free(current->key);
            if(current->value)
                free(current->value);
            free(current);
            current = next;
        }
        current = down;
    }

    free(map);
    *orderd_map = NULL;
}