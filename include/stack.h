
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

stack* stack_init();
stack* stack_push(stack* s, const void* data, size_t size);
void* stack_pop(stack* s);
void* stack_peek(stack* s);
int stack_is_empty(stack* s);
int stack_search(stack* s, const void* data, int (*compare)(const void*, const void*));
void stack_clear(stack** s);
unsigned int stack_length(stack *s);
