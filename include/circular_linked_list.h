/*

#define NEW_NODE() ((struct circular_list_node*)malloc(sizeof(struct circular_list_node)))

struct circular_list_node{
    void* data;
    struct circular_list_node* next;
};

struct circular_linked_list{
    struct circular_list_node *head;
};

typedef struct circular_list_node circular_list_node;
typedef struct circular_linked_list circular_linked_list;

circular_list_node* list_insert(circular_list_node* head, const void *data, size_t size);
circular_list_node* list_insert_first(circular_list_node* head, const void* data, size_t size);
circular_list_node* list_insert_last(circular_list_node* head, const void *data, size_t size );
circular_list_node* list_insert_at(circular_list_node* head, const void* data, size_t size, unsigned int index);

circular_list_node* list_get_node(circular_list_node* head, unsigned const int index);
void* list_first(circular_list_node* head);
void* list_last(circular_list_node *head);
void* list_get(circular_list_node *head, unsigned const int index);
int list_index_of(circular_list_node* head, const void *data, int (*compare)(const void*, const void*));
int list_last_index_of(circular_list_node* head, const void *data, int (*compare)(const void*, const void*));
int list_contains(circular_list_node* head, const void *data, int (*compare)(const void*, const void*));

circular_list_node* list_remove_first(circular_list_node *head);
circular_list_node* list_remove_last(circular_list_node* head);
circular_list_node* list_remove_at(circular_list_node* head, unsigned const int index);
circular_list_node* list_remove_value(circular_list_node* head, const void *value, int (*compare)(const void*, const void*));

circular_list_node* list_update(circular_list_node* head, const void *old_data, const void *new_data, size_t size, int (*compare)(const void*, const void*) );
circular_list_node* list_reverse(circular_list_node* head);
circular_list_node* list_clone(circular_list_node* head, size_t size);
circular_list_node* list_append(circular_list_node* head1, circular_list_node* head2);
void list_clear(circular_list_node * head);
unsigned int list_length(circular_list_node* head);

*/