/*
    Like an ordered dictionary
*/

#ifndef SKIP_LIST_MAP
#define SKIP_LIST_MAP

#define NEWNODE (struct skip_list_map_node*)malloc(sizeof(struct skip_list_map_node))

struct skip_list_map_node{
    void *key;
    void *value;
    unsigned int level;
    struct skip_list_map_node *next;
    struct skip_list_map_node *down;
};

struct skip_list_map{
    struct skip_list_map_node *head;
    float p;
    unsigned int size;
};

typedef struct skip_list_map_node skip_list_map_node;
typedef struct skip_list_map skip_list_map;


/**
 * @brief This function initialized an empty skip list map
 * 
 * @return The empty skip list map, NULL on failure
 */
skip_list_map* skip_list_map_init();



/**
 * @brief This function creates an skip_list_map_node with gives parameters
 *        It works like a constructor
 * 
 * @param level The level of node
 * @param key The key of the node
 * @param key_size Size of the key
 * @param value The Value
 * @param value_size The size of the value
 * @param next Next node
 * @param down Down node
 * 
 * @return skip_list_node* on success, NULL otherwise
 */
skip_list_map_node* skip_list_map_create_new_node(
    unsigned int level,
    const void *key,
    size_t key_size,
    const void *value,
    size_t value_size,
    skip_list_map_node *next,
    skip_list_map_node *down
);


/**
 * @brief This function generated a random level for node
 *
 * @param
 * @return a random level
 */
int skip_list_map_random_level(skip_list_map *ordered_map);



/**
 * @brief This function add a new key-value pair into the skip list map
 * 
 * @param ordered_map skip_list_map
 * @param key The key
 * @param key_size The size of the key
 * @param value The value
 * @param value_size The size of the value
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each other
 * @return 1 on success, 0 otherwise 
 */
int skip_list_map_put(
    skip_list_map *ordered_map,
    const void *key,
    size_t key_size,
    const void *value,
    size_t value_size,
    int (*compare)(const void*, const void*)
);


/**
 * @brief This function checks if the key (element) exists in the map
 * 
 * @param ordered_map skip list map
 * @param key Key to search
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each other
 * @return 1 if key exists, 0 otherwise
 */
int skip_list_map_contains(
    skip_list_map *ordered_map, 
    const void* key, 
    int (*compare)(const void*, const void*)
);



/**
 * @brief This function gives value from key
 * 
 * @param ordered_map skip_list_map
 * @param key The key whose value will be returned
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each other
 * @return address of value, NULL otherwise
 */
void* skip_list_map_get(
    skip_list_map *ordered_map, 
    const void *key, 
    int (*compare)(const void*, const void*)
);


/**
 * @brief This function removes a key-value pair from the map
 * 
 * @param ordered_map skip list map
 * @param key Key to remove
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each other
 * 
 * @return 1 on success, 0 otherwise
 */
int skip_list_map_remove(
    skip_list_map *orderd_map, 
    const void *key, 
    int (*compare)(const void*, const void*)
);



/**
 * @brief This function clears skip list map
 * 
 * @param **list_set address of skip_list_map pointer
 */
void skip_list_map_clear(skip_list_map **orderd_map);

#endif