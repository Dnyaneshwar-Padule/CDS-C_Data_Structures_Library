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


/**
 * @brief This function created a empty linked lists
 * @return linked_list* on SUCCESS, NULL otherwise
 */
linked_list* list_init();


/**
 * @brief This function clears the linked list
 * 
 * @param l_list The linked list
 */
void list_clear(linked_list **l_list);


/**
 * @brief This function inserts a new node into the linked list at the end
 * 
 * @param l_list The linked list in which the node will be inserted
 * @param data The node will store this data
 * @param size The size of the data, so that it can copy the data into node
 * @return linked_list* on Success, NULL otherwise
 */
linked_list* list_insert(linked_list* l_list, const void *data, size_t size);


/**
 * @brief This function inserts a new node at the beginning of the linked list
 * 
 * @param l_list The linked list in which the node will be inserted
 * @param data The node will store this data
 * @param size The size of the data, so that it can copy the data into node
 * @return linked_list* on Success, NULL otherwise 
 */
linked_list* list_insert_first(linked_list* l_list, const void* data, size_t size);


/**
 * @brief This function inserts a new node at the end of the linked list
 * 
 * @param l_list The linked list in which the node will be inserted
 * @param data The node will store this data
 * @param size The size of the data, so that it can copy the data into node
 * @return linked_list* on Success, NULL otherwise
 */
linked_list* list_insert_last(linked_list* l_list, const void *data, size_t size );


/**
 * @brief This function inserts a new node into the linked list, at given index
 *
 * @param l_list The linked list in which the node will be inserted
 * @param data The node will store this data
 * @param size The size of the data, so that it can copy the data into node
 * @param index The index where the node will be inserted
 * @return linked_list* on Success, NULL otherwise
 */
linked_list* list_insert_at(linked_list* l_list, const void* data, size_t size, unsigned int index);


/**
 * @brief This function returns a list node, which is at specific index \n
 *        This function starts traversing the  linked list from index 1.
 * 
 * @param l_list The linked list, from which the node will be returned
 * @param index The indec of the node
 * @return doubly_list_node* The address of node on Success, NULL otherwise
 */
list_node* list_get_node(linked_list* l_list, unsigned const int index);


/**
 * @brief This function returns the data from the first node of the linked list
 * 
 * @param l_list The linked list pointer
 * @return void* The address of the data on success, NULL otherwise
 */
void* list_first(linked_list* l_list);


/**
 * @brief This function return the data from the last node of the  linked list
 * 
 * @param l_list The linked list pointer
 * @return void* The address of the data, NULL otherwise
 */
void* list_last(linked_list *l_list);


/**
 * @brief This function gives the first index of the node, whose data matches with given data \n
 *        This function gives 1-based index
 * 
 * @param l_list The linked list from which the data will be searched
 * @param data The data to search 
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each other
 * @return The first index of the node, -1 if data not found
 */
int list_index_of(linked_list* l_list, const void *data, int (*compare)(const void*, const void*));



/**
 * @brief This function return data from linked list from the node at given index \n
 *          This function starts traversing the linked list from index 1.
 * 
 * @param l_list The linked list, from which the data will be returned
 * @param index The index of the node
 * @return void* The address of the data on SUCCESS, NULL otherwise
 */
void* list_get(linked_list *l_list, unsigned const int index);



/**
 * @brief This function gives the last index of the node, whose data matches with given data \n
 *        This function gives 1-based index
 * 
 * @param l_list The linked list from which the data will be searched
 * @param data The data to search 
 * @param compare The compare function, which will compare given data with the data in the nodes, \n 
 *                 The compare function should return 0, if both parameters match with each other
 * @return The last index of the node, -1 if data not found 
 */
int list_last_index_of(linked_list* l_list, const void *data, int (*compare)(const void*, const void*));


/**
 * @brief This function checks if data exists in the linked list or not
 * 
 * @param l_list The linked list in which the search will happen
 * @param data The data to search
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each other
 * @return 1 if data found, 0 otherwise
 */
int list_contains(linked_list* l_list, const void *data, int (*compare)(const void*, const void*));



/**
 * @brief This function removes the first node from the linked list
 *
 * @param l_list The linked list 
 * @return linked_list* with updated head 
 */
linked_list* list_remove_first(linked_list *l_list);


/**
 * @brief This function removes the last node from the linked list
 * 
 * @param l_list The linked list, from which the last node will be removed
 * @return linked_list*, NULL on invalid conditions
 */
linked_list* list_remove_last(linked_list* l_list);



/**
 * @brief This function removes a node from the linked list, from a specific index
 *          This function starts traversal with index 1.
 * 
 * @param l_list The linked list, from which the node will be removed
 * @param index The index of the node
 * @return linked_list* on Success, NULL otherwise
 */
linked_list* list_remove_at(linked_list* l_list, unsigned const int index);



/**
 * @brief This function removes a node with matching data from the linked list 
 * @paragraph This function only removes the first node found with target value
 * 
 * @param l_list The linked list, from which the node will be removed
 * @param value The value to remove from the linked list
 * @param compare The compare function, which will compare given data with the data in the nodes, 
 *                 The compare function should return 0, if both parameters match with each other
 * @return  doubly_linked_list On success, NULL otherwise
 */
linked_list* list_remove_value(linked_list* l_list, const void *value, int (*compare)(const void*, const void*));


/**
 * @brief This function finds the old data and updates it to new data
 * 
 * @param l_list The linked list
 * @param old_data The old data to be replaced
 * @param new_data The new data to store
 * @param size The size of the new data
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each other
 * @return linked_list* on Success, NULL otherwise
 */
linked_list* list_update(linked_list* l_list, const void *old_data, const void *new_data, size_t size, int (*compare)(const void*, const void*) );


/**
 * @brief This function reverses the nodes in linked list
 * 
 * @param l_list The linked list
 * @return linked_list* with reversed nodes 
 */
linked_list* list_reverse(linked_list* l_list);


/**
 * @brief This function clones a given linked list
 * 
 * @param dest The linked list pointer which will the store the address of the cloned linked list
 * @param src The linked list from where the nodes will be copied
 * @return The linked_list* on Success, NULL otherwise (if, unable to allocate memory)
 */
linked_list* list_clone(linked_list* dest, linked_list* src, size_t size);



/**
 * @brief This function appends two linked lists
 *        The second linked list will be attached to the end of the first linked list
 * 
 * @param d_linked_list1 The first linked list
 * @param d_linked_list2 The second linked list
 */
linked_list* list_append(linked_list* head1, linked_list* head2);



/**
 * @brief This function gives the length of linked list
 * 
 * @param l_list The linked list
 * @return The length of the linked list
 */
unsigned int list_length(linked_list* l_list);
