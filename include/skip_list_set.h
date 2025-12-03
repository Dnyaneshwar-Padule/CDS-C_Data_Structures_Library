/*
    It can be used as ordered set 
*/

#ifndef SKIP_LIST_SET
#define SKIP_LIST_SET

#define NEWNODE (struct skip_list_set_node*)malloc(sizeof(struct skip_list_set_node))
#define NEW_CLEAR_NODE (struct skip_list_set_node*)calloc(1, sizeof(struct skip_list_set_node))

#define MAX_LEVEL 32

struct skip_list_set_node{
    void* key;
    unsigned int level;
    struct skip_list_set_node *next;
    struct skip_list_set_node *down;
};

struct skip_list_set{
    struct skip_list_set_node *head;
    float p; // probability
    unsigned long size;
};

typedef struct skip_list_set_node skip_list_set_node ;
typedef struct skip_list_set skip_list_set; 


/**
 * @brief This function initializes a empty skip list set
 * @return skip_list_set, NULL otherwises
 */
skip_list_set* skip_list_set_init();


/**
 * @brief This function generated a random level for node
 *
 * @param
 * @return a random level
 */
int random_level(skip_list_set *list_set);


/**
 * @brief This function adds new key (element) in the skip list set
 * 
 * @param list_set skip list set
 * @param key Element to add
 * @param size Size of the key (element)
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each other
 * 
 * @return 1 on success, 0 on failure or duplicate element
 */
int skip_list_set_add(skip_list_set *list_set, const void *key, size_t size, int (*compare)(const void*, const void*));



/**
 * @brief This function checks if the key (element) exists in the set
 * 
 * @param list_set skip list set
 * @param key Element to add
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each other
 * @return 1 if key exists, 0 otherwise
 */
int skip_list_set_contains(skip_list_set *list_set, const void* key, int (*compare)(const void*, const void*));


/**
 * @brief This function removes a key from the list set
 * 
 * @param list_set skip list set
 * @param key Element to add
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each other
 * 
 * @return 1 on success, 0 otherwise
 */
int skip_list_set_remove(skip_list_set *list_set, const void *key, int (*compare)(const void*, const void*));


/**
 * @brief This function gives size (count of total elements) of skip list set 
 * 
 * @param list_set skip list set
 * @return size of the skip list set
 */
unsigned long skip_list_set_size(skip_list_set *list_set );


/**
 * @brief This function clears skip list set
 * 
 * @param **list_set address of skip_list_set pointer
 */
void skip_list_set_clear(skip_list_set **list_set);

#endif