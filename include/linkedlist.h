#define NEWNODE() ((struct list_node*)malloc(sizeof(struct list_node)))

struct list_node{
    void *data;
    struct list_node *next;
};

typedef struct list_node list_node;

list_node* list_insert(list_node* head, const void *data, size_t size);
list_node* list_insert_first(list_node* head, const void* data, size_t size);
list_node* list_insert_last(list_node* head, const void *data, size_t size );
list_node* list_insert_at(list_node* head, const void* data, size_t size, unsigned int index);

list_node* list_get_node(list_node* head, unsigned const int index);
void* list_first(list_node* head);
void* list_last(list_node *head);
void* list_get(list_node *head, unsigned const int index);
int list_index_of(list_node* head, const void *data, int (*compare)(const void*, const void*));
int list_last_index_of(list_node* head, const void *data, int (*compare)(const void*, const void*));
int list_contains(list_node* head, const void *data, int (*compare)(const void*, const void*));

list_node* list_remove_first(list_node *head);
list_node* list_remove_last(list_node* head);
list_node* list_remove_at(list_node* head, unsigned const int index);
list_node* list_remove_value(list_node* head, const void *value, int (*compare)(const void*, const void*));

list_node* list_update(list_node* head, const void *old_data, const void *new_data, size_t size, int (*compare)(const void*, const void*) );
list_node* list_reverse(list_node* head);
list_node* list_clone(list_node* head, size_t size);
list_node* list_append(list_node* head1, list_node* head2);
void list_clear(list_node * head);
unsigned int list_length(list_node* head);
