#define NEWNODE() ((struct list_node*)malloc(sizeof(struct list_node)))

struct list_node{
    void *data;
    struct list_node *next;
};

struct linked_list{
    struct list_node *head;
};

typedef struct list_node list_node;
typedef struct linked_list linked_list;

linked_list* list_init();
void list_clear(linked_list **l_list);

linked_list* list_insert(linked_list* l_list, const void *data, size_t size);
linked_list* list_insert_first(linked_list* l_list, const void* data, size_t size);
linked_list* list_insert_last(linked_list* l_list, const void *data, size_t size );
linked_list* list_insert_at(linked_list* l_list, const void* data, size_t size, unsigned int index);

list_node* list_get_node(linked_list* l_list, unsigned const int index);
void* list_first(linked_list* l_list);
void* list_last(linked_list *l_list);
void* list_get(linked_list *l_list, unsigned const int index);
int list_index_of(linked_list* l_list, const void *data, int (*compare)(const void*, const void*));
int list_last_index_of(linked_list* l_list, const void *data, int (*compare)(const void*, const void*));
int list_contains(linked_list* l_list, const void *data, int (*compare)(const void*, const void*));

linked_list* list_remove_first(linked_list *l_list);
linked_list* list_remove_last(linked_list* l_list);
linked_list* list_remove_at(linked_list* l_list, unsigned const int index);
linked_list* list_remove_value(linked_list* l_list, const void *value, int (*compare)(const void*, const void*));

linked_list* list_update(linked_list* l_list, const void *old_data, const void *new_data, size_t size, int (*compare)(const void*, const void*) );
linked_list* list_reverse(linked_list* l_list);
linked_list* list_clone(linked_list* dest, linked_list* src, size_t size);
linked_list* list_append(linked_list* head1, linked_list* head2);
unsigned int list_length(linked_list* l_list);
