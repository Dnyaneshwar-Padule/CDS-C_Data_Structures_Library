#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/queue.h"

// simple compare function for integers
int compare_int(const void *a, const void *b) {
    int x = *(int*)a;
    int y = *(int*)b;
    if (x == y) return 0;
    return (x < y) ? -1 : 1;
}

int main() {
    Queue q = {NULL, NULL};   // rear = NULL, front = NULL

    int a = 10, b = 20, c = 30;

    // enqueue
    queue_enqueue(&q, &a, sizeof(int));
    queue_enqueue(&q, &b, sizeof(int));
    queue_enqueue(&q, &c, sizeof(int));

    printf("Queue after enqueue:\n");
    queue_node *t = q.front;
    while(t) {
        printf("%d ", *(int*)t->data);
        t = t->next;
    }
    printf("\n");

    // peek
    int *peek_val = (int*)queue_peek(&q);
    if(peek_val)
        printf("Peek: %d\n", *peek_val);

    // search
    int key = 20;
    int idx = search(&q, &key, compare_int);
    printf("Index of 20: %d\n", idx);

    // dequeue
    int *removed = (int*)queue_dequeue(&q);
    printf("Dequeued: %d\n", *removed);
    free(removed);    // user must free popped data

    printf("Queue after dequeue:\n");
    t = q.front;
    while(t) {
        printf("%d ", *(int*)t->data);
        t = t->next;
    }
    printf("\n");

    printf("Length: %u\n", queue_length(&q));

    // display rear
    if(q.rear)
        printf("Rear: %d\n", *(int*)q.rear->data);

    // clear
    queue_free(&q);

    if(queue_is_empty(&q))
        printf("Queue cleared successfully.\n");

    return 0;
}
