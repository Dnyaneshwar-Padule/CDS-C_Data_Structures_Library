#include <stdio.h>
#include <string.h>
#include "../include/linkedlist.h"

// Compare function for integers
int compare_int(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return (x > y) - (x < y);   // returns 1, 0, -1
}

int main() {

    list_node* head = NULL;

    int a = 10, b = 20, c = 30, d = 40, e = 50;

    printf("----- INSERT TESTS -----\n");
    head = list_insert_first(head, &a, sizeof(int));   // 10
    head = list_insert_last(head,  &b, sizeof(int));   // 10 -> 20
    head = list_insert_last(head,  &c, sizeof(int));   // 10 -> 20 -> 30
    head = list_insert_at(head,    &d, sizeof(int), 2); // 10 -> 40 -> 20 -> 30

    printf("List after inserts: ");
    for(int i = 1; i <= list_length(head); i++){
        printf("%d ", *(int*)list_get(head, i));
    }
    printf("\n\n");


    printf("----- GET TESTS -----\n");
    printf("First element: %d\n", *(int*)list_first(head));
    printf("Last element:  %d\n", *(int*)list_last(head));
    printf("Element at 2:  %d\n", *(int*)list_get(head, 2));
    printf("\n");


    printf("----- LENGTH TEST -----\n");
    printf("Length: %u\n\n", list_length(head));


    printf("----- CONTAINS / INDEX TEST -----\n");
    printf("Contains 20? %s\n", list_contains(head, &b, compare_int) ? "YES" : "NO");
    printf("Index of 30: %d\n\n", list_index_of(head, &c, compare_int));


    printf("----- REMOVE TESTS -----\n");
    head = list_remove_first(head);  // remove 10
    head = list_remove_last(head);   // remove 30

    printf("List after remove first & last: ");
    for(int i = 1; i <= list_length(head); i++){
        printf("%d ", *(int*)list_get(head, i));
    }
    printf("\n");

    head = list_remove_at(head, 1);  // remove index 1 (40)

    printf("List after remove_at(1): ");
    for(int i = 1; i <= list_length(head); i++){
        printf("%d ", *(int*)list_get(head, i));
    }
    printf("\n\n");


    printf("----- UPDATE -----\n");
    int new_val = 999;
    head = list_insert_last(head, &e, sizeof(int));  // add 50
    head = list_update(head, &e, &new_val, sizeof(int), compare_int);

    printf("List after update 50→999: ");
    for(int i = 1; i <= list_length(head); i++){
        printf("%d ", *(int*)list_get(head, i));
    }
    printf("\n\n");


    printf("----- CLONE -----\n");
    list_node* clone = list_clone(head, sizeof(int));

    printf("Cloned list: ");
    for(int i = 1; i <= list_length(clone); i++){
        printf("%d ", *(int*)list_get(clone, i));
    }
    printf("\n\n");


    printf("----- REVERSE -----\n");
    head = list_reverse(head);

    printf("Reversed list: ");
    for(int i = 1; i <= list_length(head); i++){
        printf("%d ", *(int*)list_get(head, i));
    }
    printf("\n\n");


    printf("----- APPEND -----\n");
    head = list_append(head, clone);   // append cloned list

    printf("After append: ");
    for(int i = 1; i <= list_length(head); i++){
        printf("%d ", *(int*)list_get(head, i));
    }
    printf("\n\n");


    printf("----- CLEAR -----\n");
    list_clear(head);
    printf("List cleared.\n");

    return 0;
}
