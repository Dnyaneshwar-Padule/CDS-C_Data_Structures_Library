
#define NEW_NODE() ((stack_node*)malloc(sizeof(stack_node)))
#define BOTTOM NULL

struct stack_node{
    struct stack_node *previous;
    void *data;
    struct stack_node *next;
};

struct stack{
    struct stack_node *top;
};

typedef struct stack_node stack_node;
typedef struct stack stack;


/**
 * @brief This function creates a empty Stack
 * @return address of stack on success, NULL otherwise
 */
stack* stack_init();


/**
 * @brief This function (inserts) pushes new data into the stack
 * 
 * @param s The stack
 * @param data The data to insert
 * @param size the size of the data
 * @return address of the stack on success, NULL otherwise
 */
stack* stack_push(stack* s, const void* data, size_t size);


/**
 * @brief This function delets the topmost node and gives it's data
 * 
 * @param s The stack
 * @return The address of the data, NULL otherwise
 */
void* stack_pop(stack* s);


/**
 * @brief This function gives the data from the topmost node
 * 
 * @param s The stack
 * @return The address of the data, NULL otherwise
 */
void* stack_peek(stack* s);


/**
 * @brief This function tells if the stack is empty
 * 
 * @param s The stack
 * @return 1 if the stack is empty, 0 otherwise
 */
int stack_is_empty(stack* s);

/**
 * @brief This function searches data in the stack
 * 
 * @param s The stack
 * @param data The data to search
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each othe
 * @return index of the node containing data, -1 otherwise
 */
int stack_search(stack* s, const void* data, int (*compare)(const void*, const void*));


/**
 * @brief This function clears the stack
 * 
 * @param s The stack
 */
void stack_clear(stack** s);



/**
 * @brief This function gives the size of the stack
 * 
 * @param s The stack
 * @return The size of the stack
 */
unsigned int stack_length(stack *s);
