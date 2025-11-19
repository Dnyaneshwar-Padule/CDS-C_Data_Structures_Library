#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NEW_NODE() ((struct doubly_list_node*)malloc(sizeof(struct doubly_list_node)))

struct doubly_list_node{
    void* data;
    struct doubly_list_node* next;
    struct doubly_list_node* previous;
};

struct doubly_linked_list{
    struct doubly_list_node *head;
};

typedef struct doubly_list_node doubly_list_node;
typedef struct doubly_linked_list doubly_linked_list;

void init(doubly_linked_list *d_liked_list);

doubly_linked_list* doubly_list_insert(doubly_linked_list* d_linked_list, const void *data, size_t size);
doubly_linked_list* doubly_list_insert_first(doubly_linked_list* d_linked_list, const void* data, size_t size);
doubly_linked_list* doubly_list_insert_last(doubly_linked_list* d_linked_list, const void *data, size_t size );
doubly_linked_list* doubly_list_insert_at(doubly_linked_list* d_linked_list, const void* data, size_t size, unsigned int index);

doubly_list_node* doubly_list_get_node(doubly_linked_list* d_linked_list, unsigned const int index);
void* doubly_list_get(doubly_linked_list *d_linked_list, unsigned const int index);
void* doubly_list_first(doubly_linked_list* d_linked_list);
void* doubly_list_last(doubly_linked_list *d_linked_list);

int doubly_list_index_of(doubly_linked_list* d_linked_list, const void *data, int (*compare)(const void*, const void*));
int doubly_list_last_index_of(doubly_linked_list* d_linked_list, const void *data, int (*compare)(const void*, const void*));
int doubly_list_contains(doubly_linked_list* d_linked_list, const void *data, int (*compare)(const void*, const void*));

doubly_linked_list* doubly_list_remove_first(doubly_linked_list *d_linked_list);
doubly_linked_list* doubly_list_remove_last(doubly_linked_list* d_linked_list);
doubly_linked_list* doubly_list_remove_at(doubly_linked_list* d_linked_list, unsigned const int index);
doubly_linked_list* doubly_list_remove_value(doubly_linked_list* d_linked_list, const void *value, int (*compare)(const void*, const void*));

doubly_linked_list* doubly_list_update(doubly_linked_list* d_linked_list, const void *old_data, const void *new_data, size_t size, int (*compare)(const void*, const void*) );
doubly_linked_list* doubly_list_reverse(doubly_linked_list* d_linked_list);
doubly_linked_list* doubly_list_clone(doubly_linked_list *dest, doubly_linked_list* src, size_t size);
doubly_linked_list* doubly_list_append(doubly_linked_list* d_linked_list1, doubly_linked_list* d_linked_list2);
void doubly_list_clear(doubly_linked_list * d_linked_list);
unsigned int doubly_list_length(doubly_linked_list* d_linked_list);
