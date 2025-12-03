#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/hashset.h"


hash_set* hash_set_init(unsigned int initial_size){
    if(initial_size < 3) initial_size = 3;
    hash_set *hs = (hash_set*)malloc(sizeof(hash_set));
    if(! hs){
        fprintf(stderr, "Unable to allocate memory for hash set !\n");
        return NULL;
    }
    
    hs->set = (hash_set_node*)calloc(initial_size, sizeof(hash_set_node));
    if( ! hs->set){
        fprintf(stderr, "Unable to allocate memory for hash set !\n");
        free(hs);
        return NULL;
    }
    hs->length = initial_size;
    return hs;
}

void hash_set_clear(hash_set **hs){
    if(! hs || ! (*hs) ) return;
    node *current = NULL, *t = NULL;
    for(int i = 0; i < (*hs)->length; ++i){
        current = (*hs)->set[i].head;
        while(current){
            t = current;
            current = current->next;
            free(t->key);
            free(t);
        }
    }
    free((*hs)->set);
    free(*hs);
    *hs = NULL;
}


int hash_set_add(hash_set* hs, const void *key, size_t key_size, unsigned int(*hash)(const void*, int) ,int (*compare)(const void*, const void*)){
    if(! hs || ! key || ! hs->set) return 0;

    int index = hash(key, hs->length);

    //Invalid index
    if(index >= hs->length){
        fprintf(stderr, "Invalid hash value received from hash function !\n");
        return 0;
    }
    
    node *new_node = (node*)malloc(sizeof(node));
    if( ! new_node){
        fprintf(stderr, "Unable to allocate memory for new node!\n");
        return 0;
    }
    
    new_node->key = malloc(key_size);
    if(! new_node->key){
        fprintf(stderr, "Unable to allocate memory for key !\n");
        free(new_node);
        return 0;
    }

    //Copying key
    memcpy(new_node->key, key, key_size);
    new_node->next = NULL;

    node * current = hs->set[index].head, *previous = NULL;

    while (current){
        previous = current;
        if(compare(key, current->key) == 0){
            fprintf(stderr, "Key already exists !\n");
            free(new_node->key);
            free(new_node);
            return 0;
        }
        current = current->next;
    }

    // head is null
    if(! previous){
        hs->set[index].head = new_node;
        hs->set[index].length = 1;
    }
    else{
        previous->next = new_node;
        hs->set[index].length++;    
    }
    
    // If load factor is greater than 1, rehash the hash table
    if( (double) hash_set_size(hs) / (double) hs->length  > 1)
        rehash(hs, hash);

    return 1;
}


int hash_set_contains(hash_set* hs, const void *key,unsigned int(*hash)(const void*, int), int (*compare)(const void *, const void*) ){
    if( ! hs || ! hs->set || ! key)  return 0;

    int index = hash(key, hs->length);
    if (index >= hs->length) return 0; // Invalid index

    node* current = hs->set[index].head;
    while(current){
        if(compare(key, current->key) == 0)
            return 1;
        current = current->next;
    }

    return 0;
}


int hash_set_remove(hash_set *hs, const void *key, unsigned int(*hash)(const void*, int), int (*compare)(const void* , const void*)){
    if(! hs || ! hs->set || ! key) return 0;

    int index = hash(key, hs->length);
    if(index >= hs->length) return 0;

    node* current = hs->set[index].head, *previous = NULL;

    while(current){
        if(compare(key, current->key) == 0)
            break;
        previous = current;
        current  = current->next;
    }

    // key not found
    if(! current){
        return 0;
    }

    if(! previous){
        previous = current;
        current = current->next;
        hs->set[index].head = current;
        free(previous->key);
        free(previous);
    }
    else{
        previous->next = current->next;
        free(current->key);
        free(current);
    }
    hs->set[index].length--;
    return 1;
}


unsigned int hash_set_size(hash_set *hs){
    if(! hs || ! hs->set) return 0;
    unsigned int size = 0;
    for(int i = 0; i < hs->length; ++i)
        size += hs->set[i].length;
    return size;
}


void rehash(hash_set *hs, unsigned int (*hash)(const void*, int)){
    if(! hs || ! hs->set) return;

    int new_length = hs->length * 2, index = 0;
    hash_set *new_set = hash_set_init(new_length);
    node* current = NULL, *t = NULL;

    for(int i = 0; i < hs->length; ++i){
        current = hs->set[i].head;
        while(current){
            t = current->next;
            index = hash(current->key, new_length);
            current->next =  new_set->set[index].head;
            new_set->set[index].head = current;
            new_set->set[index].length++;
            current =  t ;
        }
    }

    free(hs->set);
    hs->set = new_set->set;
    hs->length = new_set->length;
    free(new_set);
}
