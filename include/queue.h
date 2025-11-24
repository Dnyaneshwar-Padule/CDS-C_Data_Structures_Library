
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

Queue* queue_init();
Queue* queue_enqueue(Queue* queue, const void* data, size_t size);
void* queue_dequeue(Queue *queue);
void* queue_peek(Queue* queue);
unsigned int queue_length(Queue* queue);
void queue_free(Queue **queue);
int queue_is_empty(Queue *queue);
int search(Queue* queue, const void* data, int (*compare)(const void*, const void*));

