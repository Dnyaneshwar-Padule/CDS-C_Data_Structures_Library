#define NEW_NODE() ((struct node*)malloc(sizeof(struct node)))
#define NEW_HASH_TABLE_NODE() (struct hash_table_node*)(malloc(sizeof(struct hash_table_node)))

// contains data, the actual list
struct node{
    void *key;
    void *value;
    struct node* next;
};

struct hash_table_node{
    unsigned int length;
    struct node *head;    
};

struct hash_table{
    unsigned int length;
    struct hash_table_node *table;
};

typedef struct node node;
typedef struct hash_table_node hash_table_node;
typedef struct hash_table hash_table;


hash_table* hash_table_init(unsigned int initial_table_length);
void hash_table_clear(hash_table *ht);
int hash_table_put(hash_table* ht, const void *key, size_t key_size, const void *value, size_t value_size, unsigned int  (*hash)(const void*, int), int (*compare)(const void *, const void*));
int hash_table_contains_key(hash_table* ht, const void *key, unsigned int  (*hash)(const void*, int), int (*compare)(const void *, const void*));
int hash_table_remove(hash_table *ht, const void *key, unsigned int  (*hash)(const void*, int), int (*compare)(const void *, const void*));
void* hash_table_get(hash_table *ht, const void *key, unsigned int  (*hash)(const void*, int), int (*compare)(const void *, const void*));
unsigned int hash_table_size(hash_table *ht);
void rehash(hash_table* ht, unsigned int  (*hash)(const void*, int));

// clone()
// containsValue()
