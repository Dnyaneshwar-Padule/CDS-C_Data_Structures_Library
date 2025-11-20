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
        fprintf(stderr, "Unable to allocate memory for hash table !\n");
        return;
    }
    ht->length = initial_table_length;
    // no need to assign null to all heads, calloc does this
}

int hash_table_put(hash_table* ht, const void *key, size_t key_size, const void *value, size_t value_size, unsigned int (*hash)(const void*, int), int (*compare)(const void *, const void*)){
    if(! ht || ! key || ! value ) return 0;

    // if table is empty, initialize an hashtable of length 3
    if( ! ht->table )
        hash_table_init(ht, 3);

    unsigned int index = hash(key, ht->length);
    
    if (index < 0 || index >= ht->length )  // invalid index
        return 0; 

    node *new_node = NEW_NODE();
    node *current = NULL, *previous = NULL;

    if( ! new_node ) 
        return 0;

    new_node->key = malloc(key_size);
    if( ! new_node->key ){
        free(new_node);
        return 0;
    }

    new_node->value = malloc(value_size);
    if( ! new_node->value){
        free(new_node->key);
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
        if( (double)hash_table_size(ht) / (double) ht->length > 1 )
            rehash(ht, hash);
        return 1;
    }

    // go to the last node,
    // we can add new node at first, but it won't check if the key already exists
    // so, we have to traverse
    while(current){
        if( compare(key, current->key) == 0 ){
           break;
        }
        previous = current;
        current = current->next;
    }
    
    if( current ){
        free(current->value);
        free(current->key);
        current->key = new_node->key;
        current->value = new_node->value;
        free(new_node);
        if( (double)hash_table_size(ht) / (double) ht->length > 1 )
            rehash(ht, hash);
        return 1;
    }
    
    previous->next = new_node;
    ht->table[index].length++;
    if( (double)hash_table_size(ht) / (double) ht->length > 1 )
        rehash(ht, hash);
    return 1;
}

void* hash_table_get(hash_table *ht, const void *key, unsigned int  (*hash)(const void*, int), int (*compare)(const void *, const void*)){
    if(! ht || ! ht->table || ! key)return NULL;
    int index = hash(key, ht->length);
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
    if ( ! ht || ! ht->table ) return;
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

int hash_table_contains_key(hash_table* ht, const void *key, unsigned int  (*hash)(const void*, int), int (*compare)(const void *, const void*)){
    if(! ht || ! ht->table || ! key)return 0;
    int index = hash(key, ht->length);
    if(index < 0 || index >= ht->length) return 0;
    node* current = ht->table[index].head;

    while(current){
        if( compare(key, current->key) == 0 )
            return 1;
        current = current->next;
    }

    return 0;
}

int hash_table_remove(hash_table *ht, const void *key, unsigned int  (*hash)(const void*, int), int (*compare)(const void *, const void*)){
    if(! ht || ! ht->table || ! key) return 0;
    int index = hash(key, ht->length);

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
        free(current);
        return 1;
    }
}

unsigned int hash_table_size(hash_table *ht){
    if( ! ht || ! ht->table) return 0;
    unsigned int cnt = 0;
    for (int i = 0; i < ht->length; i++)
        cnt += ht->table[i].length;
    return cnt;
}

void rehash(hash_table* ht, unsigned int  (*hash)(const void*, int)){
    if (! ht || ! ht->table) return;
    hash_table h;  
    hash_table_init(&h, ht->length * 2); // create a new hash table of double size
    int index ;
    node *current = NULL;
    node *next = NULL;

    for(int i = 0; i < ht->length; i++){
        current = ht->table[i].head;
        while(current){
            next = current->next;
            index = hash(current->key, h.length);
            current->next = h.table[index].head;
            h.table[index].head = current;
            h.table[index].length++;
            current = next;
        }
    }

    // free old hashtable
    free(ht->table);

    // get pointers of the new table
    ht->length = h.length;
    ht->table = h.table;
}