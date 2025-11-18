#include <stdio.h>
#include <string.h>
#include "../include/doublylinkedlist.h"

// Compare function for integers
int compare_int(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return (x > y) - (x < y);   // returns 1, 0, -1
}

void print_list(doubly_list_node* head) {
    while (head) {
        printf("%d ", *(int*)head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {

    doubly_list_node* head = NULL;

    int a = 10, b = 20, c = 30, d = 40, e = 50;

    printf("----- INSERT TESTS -----\n");
    head = doubly_list_insert_first(head, &a, sizeof(int));   // 10
    head = doubly_list_insert_last(head,  &b, sizeof(int));   // 10 -> 20
    head = doubly_list_insert_last(head,  &c, sizeof(int));   // 10 -> 20 -> 30
    head = doubly_list_insert_at(head,    &d, sizeof(int), 2); // 10 -> 40 -> 20 -> 30

    printf("List after inserts: ");
    print_list(head);
    printf("\n");


    printf("----- GET TESTS -----\n");
    printf("First element: %d\n", *(int*)doubly_list_first(head));
    printf("Last element:  %d\n", *(int*)doubly_list_last(head));
    printf("Element at 2:  %d\n", *(int*)doubly_list_get(head, 2));
    printf("\n");


    printf("----- LENGTH TEST -----\n");
    printf("Length: %u\n\n", doubly_list_length(head));


    printf("----- CONTAINS / INDEX TEST -----\n");
    printf("Contains 20? %s\n",
           doubly_list_contains(head, &b, compare_int) ? "YES" : "NO");
    printf("Index of 30: %d\n\n",
           doubly_list_index_of(head, &c, compare_int));


    printf("----- REMOVE TESTS -----\n");
    head = doubly_list_remove_first(head);  // remove 10
    head = doubly_list_remove_last(head);   // remove 30

    printf("List after remove first & last: ");
    print_list(head);

    head = doubly_list_remove_at(head, 1);  // remove 40

    printf("List after remove_at(1): ");
    print_list(head);
    printf("\n");


    printf("----- UPDATE -----\n");
    int new_val = 999;
    head = doubly_list_insert_last(head, &e, sizeof(int));  // add 50
    head = doubly_list_update(head, &e, &new_val, sizeof(int), compare_int);

    printf("List after update 50->999: ");
    print_list(head);
    printf("\n");


    printf("----- CLONE -----\n");
    doubly_list_node* clone = doubly_list_clone(head, sizeof(int));

    printf("Cloned list: ");
    print_list(clone);
    printf("\n");


    printf("----- REVERSE -----\n");
    head = doubly_list_reverse(head);

    printf("Reversed list: ");
    print_list(head);
    printf("\n");


    printf("----- APPEND -----\n");
    head = doubly_list_append(head, clone);

    printf("After append: ");
    print_list(head);
    printf("\n");


    printf("----- CLEAR -----\n");
    doubly_list_clear(head);
    printf("List cleared.\n");

    return 0;
}
