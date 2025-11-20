#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../include/hashtable.h"

void hash_table_init(hash_table* ht, unsigned int initial_table_length){
    if( !ht ) return;
    if(initial_table_length < 1) return;

    // This will create the hash_map_array
    ht->table = (hash_table_node*)calloc(initial_table_length, sizeof(hash_table_node));
    if(!ht->table){
        fprintf(stdin, "Unable to allocate memory for hash table !\n");
        return;
    }
    ht->length = initial_table_length;
    // no need to assign null to all heads, calloc does this
}

int hash_table_put(hash_table* ht, const void *key, size_t key_size, const void *value, size_t value_size, unsigned int (*hash)(const void* key), int (*compare)(const void *, const void*)){
    if(! ht ) return 0;
    if(! key || ! value) return 0;

    unsigned int index = hash(key);
    
    if (index < 0 || index >= ht->length )  // invalid index
        return 0; 

    node *new_node = NEW_NODE();
    node *current = NULL;

    if( ! new_node ) 
        return 0;

    new_node->key = malloc(key_size);
    if( ! new_node->key ){
        free(new_node);
        return 0;
    }

    new_node->value = malloc(value_size);
    if( ! new_node->value){
        free(new_node);
        return 0;
    }

    memcpy(new_node->key, key, key_size);
    memcpy(new_node->value, value, value_size);
    new_node->next = NULL;

    // traverse
    current = ht->table[index].head;
    if(! current){
        ht->table[index].head = new_node;
        ht->table[index].length = 1;
        return 1;
    }

    while(current->next){
        if( compare(key, current->key) == 0 ){
            free(current->value);
            current->value = new_node->value;
            free(new_node->key);
            free(new_node);
            return 1;
        }
        current = current->next;
    }
    
    if( compare(key, current->key) == 0 ){
        free(current->value);
        current->value = new_node->value;
        free(new_node->key);
        free(new_node);
        return 1;
    }
    
    current->next = new_node;
    ht->table[index].length++;
    return 1;
}

void* hash_table_get(hash_table *ht, const void *key, unsigned int (*hash)(const void *), int (*compare)(const void *, const void*)){
    if(! ht || ! key)return NULL;
    int index = hash(key);
    node* current = NULL;

    //invalid index
    if(index < 0 || index >= ht->length)
        return NULL;

    current = ht->table[index].head;

    // search for the key
    while ( current ){
        if (compare(key, current->key) == 0){
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void hash_table_clear(hash_table *ht){
    if ( ! ht ) return;
    node *current = NULL, *previous = NULL;

    for(int i = 0; i < ht->length; i++){
        current = ht->table[i].head;
        while (current){
            previous = current;
            current = current->next;
            free(previous->value);
            free(previous->key);
            free(previous);
        }
    }
}

int hash_table_contains_key(hash_table* ht, const void *key, unsigned int (*hash)(const void*), int (*compare)(const void *, const void*)){
    if(! ht )return 0;
    int index = hash(key);
    if(index < 0 || index >= ht->length) return 0;
    node* current = ht->table[index].head;

    while(current){
        if( compare(key, current->key) == 0 )
            return 1;
        current = current->next;
    }

    return 0;
}

int hash_table_remove(hash_table *ht, const void *key, unsigned int (*hash)(const void*), int (*compare)(const void *, const void*)){
    if(! ht) return 0;
    int index = hash(key);

    if(index < 0 || index >= ht->length)
        return 0;

    node *current = ht->table[index].head;
    node* previous = NULL;

    while(current){
        if(compare(key, current->key) == 0){
            break;
        }
        previous = current;
        current = current->next;
    }

    if( ! current) return 0;

    // removing head node
    if(! previous){
        previous = current;
        current = current->next;
        ht->table[index].head = current;
        ht->table[index].length--;
        free(previous->key);
        free(previous->value);
        free(previous);
        return 1;
    }
    else{
        previous->next = current->next;
        ht->table[index].length--;
        free(current->key);
        free(current->value);
        free(current->key);
        return 1;
    }
}
