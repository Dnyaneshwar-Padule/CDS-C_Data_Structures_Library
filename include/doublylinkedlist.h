#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NEW_NODE() ((struct doubly_list_node*)malloc(sizeof(struct doubly_list_node)))

struct doubly_list_node{
    void* data;
    struct doubly_list_node* next;
    struct doubly_list_node* previous;
};

typedef struct doubly_list_node doubly_list_node;

doubly_list_node* doubly_list_insert(doubly_list_node* head, const void *data, size_t size);
doubly_list_node* doubly_list_insert_first(doubly_list_node* head, const void* data, size_t size);
doubly_list_node* doubly_list_insert_last(doubly_list_node* head, const void *data, size_t size );
doubly_list_node* doubly_list_insert_at(doubly_list_node* head, const void* data, size_t size, unsigned int index);

doubly_list_node* doubly_list_get_node(doubly_list_node* head, unsigned const int index);
void* doubly_list_get(doubly_list_node *head, unsigned const int index);
void* doubly_list_first(doubly_list_node* head);
void* doubly_list_last(doubly_list_node *head);

int doubly_list_index_of(doubly_list_node* head, const void *data, int (*compare)(const void*, const void*));
int doubly_list_last_index_of(doubly_list_node* head, const void *data, int (*compare)(const void*, const void*));
int doubly_list_contains(doubly_list_node* head, const void *data, int (*compare)(const void*, const void*));

doubly_list_node* doubly_list_remove_first(doubly_list_node *head);
doubly_list_node* doubly_list_remove_last(doubly_list_node* head);
doubly_list_node* doubly_list_remove_at(doubly_list_node* head, unsigned const int index);
doubly_list_node* doubly_list_remove_value(doubly_list_node* head, const void *value, int (*compare)(const void*, const void*));

doubly_list_node* doubly_list_update(doubly_list_node* head, const void *old_data, const void *new_data, size_t size, int (*compare)(const void*, const void*) );
doubly_list_node* doubly_list_reverse(doubly_list_node* head);
doubly_list_node* doubly_list_clone(doubly_list_node* head, size_t size);
doubly_list_node* doubly_list_append(doubly_list_node* head1, doubly_list_node* head2);
void doubly_list_clear(doubly_list_node * head);
unsigned int doubly_list_length(doubly_list_node* head);
