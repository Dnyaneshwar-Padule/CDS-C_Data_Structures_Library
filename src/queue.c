#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "../include/queue.h"

Queue* queue_init(){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if(! queue) return NULL;
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int queue_is_empty(Queue* queue){
    if(! queue) return 1;
    return queue->front == NULL;
}

Queue* queue_enqueue(Queue* queue, const void* data, size_t size){
    if(! queue)
        queue = queue_init();

    if(! queue){
        fprintf(stderr, "Unable to allocate memory for Queue !\n");
        return NULL;
    }

    queue_node* new_node = NEW_NODE();
    if(! new_node){
        fprintf(stderr, "Queue is full !\n");
        return queue;
    }
    
    new_node->data = malloc(size);
    if(! new_node->data){
        fprintf(stderr, "Unable to allocate memory for data !\n");
        free(new_node);
        return queue;
    }

    memcpy(new_node->data, data, size);
    new_node->next = NULL;
    new_node->previous = NULL;

    if(queue_is_empty(queue)){
        queue->rear = new_node;
        queue->front = new_node;
        return queue;
    }

    new_node->previous = queue->rear;
    queue->rear->next = new_node;
    queue->rear = new_node;
    return queue;
}

void* queue_dequeue(Queue *queue){
    if(queue_is_empty(queue)) return NULL;

    queue_node *next = queue->front->next; 
    void *data = queue->front->data;
    if(next) next->previous = NULL;
    free( queue->front );
    queue->front = next;
    if(! queue->front) queue->rear = NULL;
    return data;
}

void* queue_peek(Queue *queue){
    if(queue_is_empty(queue)) return NULL;
    return queue->front->data;
}

unsigned int queue_length(Queue* queue){
    if(! queue) return 0;
    unsigned int length = 0;
    queue_node * current = queue->front;

    while(current){
        length++;
        current = current->next;
    }
    return length;
}

void queue_free(Queue **queue){
    if( ! *queue ) return;
    queue_node *current = (*queue)->front;
    while ((*queue)->front){
        current = (*queue)->front;
        (*queue)->front = (*queue)->front->next;
        free(current->data);
        free(current);
    }
    free(queue);
    *queue = NULL;
}

int search(Queue *queue, const void* data, int (*compare)(const void*, const void*)){
    if(queue_is_empty(queue)) return -1;

    int index = 1;
    queue_node* current = queue->front;

    while (current){
        if (compare(data, current->data) == 0)
            return index;
        index++;
        current = current->next;
    }
    return -1;
}