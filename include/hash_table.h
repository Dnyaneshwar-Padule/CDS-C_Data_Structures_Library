#ifndef HASH_TABLE_H
#define HASH_TABLE_H

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


/**
 * @brief This function creates a hashtable with minimum initial size 2
 * 
 * @param initial_table_length The initial size of the hash Table
 * @return address of the hash_table on success, NULL otherwise
 */
hash_table* hash_table_init(unsigned int initial_table_length);


/**
 * @brief This function clears the hash table
 * 
 * @param ht The address of hash_table pointer
 */
void hash_table_clear(hash_table **ht);



/**
 * @brief This function inserts a new (key-value) pair into the hash table
 * 
 * @param ht The hash table in which the pair needs to be inserted
 * @param key The key 
 * @param key_size The size of the key
 * @param value The value
 * @param value_size The size of the value
 * @param hash The hash function, which accepts key and hash table length, and return hashed index for the key
 * @param compare The compare function, it check if the key already exists in the hashtable or nots \n
 *                  The compare function should return 0 if both values are equal
 * @return 1 On success, 0 otherwise 
 */
int hash_table_put(
    hash_table* ht, 
    const void *key, 
    size_t key_size, 
    const void *value, 
    size_t value_size, 
    unsigned int  (*hash)(const void*, int), 
    int (*compare)(const void *, const void*)
);


/**
 * @brief This function checks if a key exists in the hash_table
 * 
 * @param ht The hash table
 * @param key The key to check
 * @param hash The hash function, which accepts key and hash table length, and return hashed index for the key
 * @param compare The compare function, it check if the key already exists in the hashtable or nots \n
 *                  The compare function should return 0 if both values are equal
 * @return 1 if the key exists, 0 otherwise 
 */
int hash_table_contains_key(
    hash_table* ht, 
    const void *key, 
    unsigned int  (*hash)(const void*, int), 
    int (*compare)(const void *, const void*)
);


/**
 * @brief This function removes a (key-value) pair from the hash table
 * 
 * @param ht The hash table
 * @param key Key to remove
 * @param hash The hash function, which accepts key and hash table length, and return hashed index for the key
 * @param compare The compare function, it check if the key already exists in the hashtable or nots \n
 *                  The compare function should return 0 if both values are equal
 * @return 1 on success, 0 otherwise
 */
int hash_table_remove(
    hash_table *ht, 
    const void *key, 
    unsigned int  (*hash)(const void*, int), 
    int (*compare)(const void *, const void*)
);


/**
 * @brief This function return value, whose key matches with give key
 * 
 * @param ht The hash table
 * @param key The key to search
 * @param hash The hash function, which accepts key and hash table length, and return hashed index for the key
 * @param compare The compare function, it check if the key already exists in the hashtable or nots \n
 *                  The compare function should return 0 if both values are equal
 * @return address of data, NULL if the key doesn't exists
 */
void* hash_table_get(
    hash_table *ht, 
    const void *key, 
    unsigned int  (*hash)(const void*, int), 
    int (*compare)(const void *, const void*)
);


/**
 * @brief This function gives the count of total pairs in the hash tale
 * 
 * @param ht The hash table
 * @return The count of total (key-value) pairs
 */
unsigned int hash_table_size(hash_table *ht);


/**
 * @brief This function rehashes the hash table. \n
 *      It extends the hash table size by doubling it
 * 
 * @param ht The hash table
 * @param hash The hash function, which accepts key and hash table length, and return hashed index for the key
 */
void rehash(hash_table* ht, unsigned int  (*hash)(const void*, int));

// clone()
// containsValue()


#endif