#ifndef HASH_SET_H
#define HASH_SET_H

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


/**
 * @brief This function creates a hash_set of minimum size 3
 * 
 * @param initial_size The initial size of the hash set
 * @return hash_set* on success, NULL otherwise  
 */
hash_set* hash_set_init(unsigned int initial_size);



/**
 * @brief This function clears the hash set
 * 
 * @param hs The hash set
 */
void hash_set_clear(hash_set **hs);



/**
 * @brief This function adds (inserts) new key in the hash table
 * 
 * @param hs The hash set
 * @param key The key to add in the hash set
 * @param key_size The size of the key
 * @param hash The hash function, which accepts key and hash set size and gives index (hashed value)
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each other
 * @return 1 on success, 0 otherwise
 */
int hash_set_add(hash_set* hs, const void *key, size_t key_size, unsigned int(*hash)(const void*, int) ,int (*compare)(const void*, const void*));




/**
 * @brief This function checks if a key exists in the hash set
 * 
 * @param hs The hash set
 * @param key The key to search
 * @param hash The hash function, which accepts key and hash set size and gives index (hashed value)
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each other
 * @return 1 if key exists, 0 otherwise
 */
int hash_set_contains(hash_set* hs, const void *key, unsigned int(*hash)(const void*, int), int (*compare)(const void *, const void*) );



/**
 * @brief This function removes a key from hash set, if it exists
 * 
 * @param hs The hash set
 * @param key The key to search
 * @param hash The hash function, which accepts key and hash set size and gives index (hashed value)
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each other
 * @return 1 on success, 0 otherwise
 */
int hash_set_remove(hash_set *hs, const void *key, unsigned int(*hash)(const void*, int), int (*compare)(const void* , const void*));


/**
 * @brief This function gives the count of keys in the hash set
 * 
 * @param hs The hash set
 * @return The size of the hash set
 */
unsigned int hash_set_size(hash_set *hs);



/**
 * @brief This function rehashes the hash set, by doubling it's slots
 * 
 * @param hs The hash set
 * @param hash The hash function, which accepts key and hash set size and gives index (hashed value)
 */
void rehash(hash_set *hs, unsigned int (*hash)(const void*, int));


#endif