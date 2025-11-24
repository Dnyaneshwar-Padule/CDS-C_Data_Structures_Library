#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    void *key;
    struct node* next;
};

struct hash_set_node{
    struct node* head;
    unsigned int length; 
};

struct hash_set{
    int length;
    struct hash_set_node *set;
};

typedef struct node node;
typedef struct hash_set_node hash_set_node;
typedef struct hash_set hash_set;

hash_set* hash_set_init(unsigned int initial_size);
void hash_set_clear(hash_set **hs);

hash_set* hash_set_init(unsigned int initial_size){
    if(initial_size < 3) initial_size = 3;
    hash_set *hs = (hash_set*)malloc(sizeof(hash_set));
    if(! hs){
        fprintf(strerror, "Unable to allocate memory for hash set !\n");
        return NULL;
    }
    
    hs->set = (hash_set_node*)calloc(initial_size, sizeof(hash_set_node));
    if( ! hs->set){
        fprintf(strerror, "Unable to allocate memory for hash set !\n");
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
    *hs = 
}