#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

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

/**
 * @brief This function created a doubly linked list (head)
 * @return doubly_linked_list* on SUCCESS, NULL otherwise
 */
doubly_linked_list* doubly_linked_list_init();


/**
 * @brief This function inserts a new node into the doubly linked list at the end
 * 
 * @param d_linked_list The doubly linked list in which the node will be inserted
 * @param data The node will store this data
 * @param size The size of the data, so that it can copy the data into node
 * @return doubly_linked_list* on Success, NULL otherwise
 */
doubly_linked_list* doubly_list_insert(
    doubly_linked_list* d_linked_list, 
    const void *data, size_t size
);


/**
 * @brief This function inserts a new node at the beginning of the doubly linked list
 * 
 * @param d_linked_list The doubly linked list in which the node will be inserted
 * @param data The node will store this data
 * @param size The size of the data, so that it can copy the data into node
 * @return doubly_linked_list* on Success, NULL otherwise 
 */
doubly_linked_list* doubly_list_insert_first(
    doubly_linked_list* d_linked_list, 
    const void* data, size_t size
);


/**
 * @brief This function inserts a new node at the end of the doubly linked list
 * 
 * @param d_linked_list The doubly linked list in which the node will be inserted
 * @param data The node will store this data
 * @param size The size of the data, so that it can copy the data into node
 * @return doubly_linked_list* on Success, NULL otherwise
 */
doubly_linked_list* doubly_list_insert_last(
    doubly_linked_list* d_linked_list, 
    const void *data, size_t size 
);


/**
 * @brief This function inserts a new node into the doubly linked list, at given index
 *
 * @param d_linked_list The doubly linked list in which the node will be inserted
 * @param data The node will store this data
 * @param size The size of the data, so that it can copy the data into node
 * @param index The index where the node will be inserted
 * @return doubly_linked_list* on Success, NULL otherwise
 */
doubly_linked_list* doubly_list_insert_at(
    doubly_linked_list* d_linked_list, 
    const void* data, size_t size, 
    unsigned int index
);


/**
 * @brief This function returns a doubly list node, which is at specific index \n
 *        This function starts traversing the doubly linked list from index 1.
 * 
 * @param d_linked_list The doubly linked list, from which the node will be returned
 * @param index The indec of the node
 * @return doubly_list_node* The address of node on Success, NULL otherwise
 */
doubly_list_node* doubly_list_get_node(
    doubly_linked_list* d_linked_list, 
    unsigned const int index
);


/**
 * @brief This function return data from doubly linked list from the node at given index
 *          This function starts traversing the doubly linked list from index 1.
 * 
 * @param d_linked_list The doubly linked list, from which the data will be returned
 * @param index The index of the node
 * @return void* The address of the data on SUCCESS, NULL otherwise
 */
void* doubly_list_get(doubly_linked_list *d_linked_list, unsigned const int index);


/**
 * @brief This function returns the data from the first node of the doubly linked list
 * 
 * @param d_linked_list The doubly linked list pointer
 * @return void* The address of the data on success, NULL otherwise
 */
void* doubly_list_first(doubly_linked_list* d_linked_list);


/**
 * @brief This function return the data from the last node of the doubly linked list
 * 
 * @param d_linked_list The doubly linked list pointer
 * @return void* The address of the data, NULL otherwise
 */
void* doubly_list_last(doubly_linked_list *d_linked_list);


/**
 * @brief This function gives the first index of the node, whose data matches with given data \n
 *        This function gives 1-based index
 * 
 * @param d_linked_list The doubly linked list from which the data will be searched
 * @param data The data to search 
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each other
 * @return The first index of the node, -1 if data not found
 */
int doubly_list_index_of(
    doubly_linked_list* d_linked_list, 
    const void *data, 
    int (*compare)(const void*, const void*)
);


/**
 * @brief This function gives the last index of the node, whose data matches with given data \n
 *        This function gives 1-based index
 * 
 * @param d_linked_list The doubly linked list from which the data will be searched
 * @param data The data to search 
 * @param compare The compare function, which will compare given data with the data in the nodes, \n 
 *                 The compare function should return 0, if both parameters match with each other
 * @return The last index of the node, -1 if data not found 
 */
int doubly_list_last_index_of(
    doubly_linked_list* d_linked_list, 
    const void *data, 
    int (*compare)(const void*, const void*)
);


/**
 * @brief This function checks if data exists in the doubly linked list or not
 * 
 * @param d_linked_list The doubly linked list in which the search will happen
 * @param data The data to search
 * @param compare The compare function, which will compare given data with the data in the nodes, 
 *                 The compare function should return 0, if both parameters match with each other
 * @return 1 if data found, 0 otherwise
 */
int doubly_list_contains(
    doubly_linked_list* d_linked_list, 
    const void *data, 
    int (*compare)(const void*, const void*)
);


/**
 * @brief This function removes the first node from the doubly linked list
 *
 * @param d_linked_list The doubly linked list 
 * @return doubly_linked_list* with updated head 
 */
doubly_linked_list* doubly_list_remove_first(doubly_linked_list *d_linked_list);


/**
 * @brief This function removes the last node from the doubly linked list
 * 
 * @param d_linked_list The doubly linked list, from which the last node will be removed
 * @return doubly_linked_list*, NULL on invalid conditions
 */
doubly_linked_list* doubly_list_remove_last(doubly_linked_list* d_linked_list);


/**
 * @brief This function removes a node from the doubly linked list, from a specific index
 *          This function starts traversal with index 1.
 * 
 * @param d_linked_list The doubly linked list, from which the node will be removed
 * @param index The index of the node
 * @return doubly_linked_list* on Success, NULL otherwise
 */
doubly_linked_list* doubly_list_remove_at(
    doubly_linked_list* d_linked_list, 
    unsigned const int index
);


/**
 * @brief This function removes a node with matching data from the doubly linked list 
 * @paragraph This function only removes the first node found with target value
 * 
 * @param d_linked_list The doubly linked list, from which the node will be removed
 * @param value The value to remove from the doubly linked list
 * @param compare The compare function, which will compare given data with the data in the nodes, 
 *                 The compare function should return 0, if both parameters match with each other
 * @return  doubly_linked_list On success, NULL otherwise
 */
doubly_linked_list* doubly_list_remove_value(
    doubly_linked_list* d_linked_list, 
    const void *value, 
    int (*compare)(const void*, const void*)
);


/**
 * @brief This function finds the old data and updates it to new data
 * 
 * @param d_linked_list The doubly linked list
 * @param old_data The old data to be replaced
 * @param new_data The new data to store
 * @param size The size of the new data
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each other
 * @return doubly_linked_list* on Success, NULL otherwise
 */
doubly_linked_list* doubly_list_update(
    doubly_linked_list* d_linked_list, 
    const void *old_data, 
    const void *new_data, size_t size, 
    int (*compare)(const void*, const void*)
);


/**
 * @brief This function reverses the nodes in doubly linked list
 * 
 * @param d_linked_list The doubly linked list
 * @return doubly_linked_list* with reversed nodes 
 */
doubly_linked_list* doubly_list_reverse(doubly_linked_list* d_linked_list);


/**
 * @brief This function clones a given doubly linked list
 * 
 * @param dest The doubly linked list pointer which will the store the address of the cloned doubly linked list
 * @param src The doubly linked list from where the nodes will be copied
 * @return The doubly_linked_list* on Success, NULL otherwise (if, unable to allocate memory)
 */
doubly_linked_list* doubly_list_clone(doubly_linked_list *dest, doubly_linked_list* src, size_t size);


/**
 * @brief This function appends two doubly linked lists
 *        The second doubly linked list will be attached to the end of the first doubly linked list
 * 
 * @param d_linked_list1 The first doubly linked list
 * @param d_linked_list2 The second doubly linked list
 */
doubly_linked_list* doubly_list_append(doubly_linked_list* d_linked_list1, doubly_linked_list* d_linked_list2);


/**
 * @brief This function clears the doubly linked list
 * 
 * @param d_linked_list The doubly linked list
 */
void doubly_list_clear(doubly_linked_list **d_linked_list);


/**
 * @brief This function gives the length of doubly_linked_list
 * 
 * @param d_linked_list The doubly linked list
 * @return The length of the doubly linked list
 */
unsigned int doubly_list_length(doubly_linked_list* d_linked_list);



#endif