
#define NEW_NODE() ((stack_node*)malloc(sizeof(stack_node)))
#define BOTTOM NULL

struct stack_node{
    struct stack_node *previous;
    void *data;
    struct stack_node *next;
};

typedef struct stack_node stack_node;

stack_node* stack_push(stack_node* top, const void* data, size_t size);
void* stack_pop(stack_node** top);
void* stack_peek(stack_node* top);
int stack_is_empty(stack_node* top);
int stack_search(stack_node* top, const void* data, int (*compare)(const void*, const void*));
void stack_clear(stack_node** top);
unsigned int stack_length(stack_node *top);
