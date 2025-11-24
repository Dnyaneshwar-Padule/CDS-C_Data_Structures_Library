
#define NEW_NODE() ((struct queue_node*)malloc(sizeof(struct queue_node)))

struct queue_node{
    struct queue_node *previous;
    void *data;
    struct queue_node *next;
};

struct queue{
    struct queue_node *rear;
    struct queue_node *front;
};

typedef struct queue_node queue_node;
typedef struct queue Queue;


/**
 * @brief This function creates a empty Queue
 * 
 * @return The address of Queue
 */
Queue* queue_init();


/**
 * @brief This function enqueues (inserts at rear) data 
 * 
 * @param queue The queue in which data will be enqueued
 * @param data The data 
 * @param size The size of the data
 * @return Queue* on success, NULL otherwise
 */
Queue* queue_enqueue(Queue* queue, const void* data, size_t size);


/**
 * @brief sThis function dequeues (removes from front) data
 * 
 * @param queue The queue
 * @return The address of the data on success, NULL otherwise
 */
void* queue_dequeue(Queue *queue);



/**
 * @brief This function gives address of the data at the front
 * 
 * @param queue The queue
 * @return The address of data, NULL otherwise
 */
void* queue_peek(Queue* queue);


/**
 * @brief This function gives the length of the queue
 * 
 * @param queue The Queue
 * @return the length of the queue
 */
unsigned int queue_length(Queue* queue);


/**
 * @brief This function clears queue
 * 
 * @param **queue, The address of the queue pointer
 */
void queue_free(Queue **queue);


/**
 * @brief This function tells if the queue is empty
 * 
 * @param queue The queue
 * @return 1 if the queue is empty, 0 otherwise
 */
int queue_is_empty(Queue *queue);


/**
 * @brief This function searches data in the queue
 * 
 * @param queue The queue
 * @param data The data to seach
 * @param compare The compare function, which will compare given data with the data in the nodes, \n
 *                 The compare function should return 0, if both parameters match with each other
 * @return index of the node containig data, -1 otherwise
 */
int search(Queue* queue, const void* data, int (*compare)(const void*, const void*));

