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

    doubly_linked_list *d_linked_list  = doubly_linked_list_init() ;

    int a = 10, b = 20, c = 30, d = 40, e = 50;

    printf("----- INSERT TESTS -----\n");
    doubly_list_insert_first(d_linked_list, &a, sizeof(int));   // 10
    doubly_list_insert_last(d_linked_list, &b, sizeof(int));   // 10 -> 20
    doubly_list_insert_last(d_linked_list, &c, sizeof(int));   // 10 -> 20 -> 30
    doubly_list_insert_at(d_linked_list, &d, sizeof(int), 2); // 10 -> 40 -> 20 -> 30

    printf("List after inserts: ");
    print_list(d_linked_list->head);
    printf("\n");


    printf("----- GET TESTS -----\n");
    printf("First element: %d\n", *(int*)doubly_list_first(d_linked_list));
    printf("Last element:  %d\n", *(int*)doubly_list_last(d_linked_list));
    printf("Element at 2:  %d\n", *(int*)doubly_list_get(d_linked_list, 2));
    printf("\n");


    printf("----- LENGTH TEST -----\n");
    printf("Length: %u\n\n", doubly_list_length(d_linked_list));


    printf("----- CONTAINS / INDEX TEST -----\n");
    printf("Contains 20? %s\n",
           doubly_list_contains(d_linked_list, &b, compare_int) ? "YES" : "NO");
    printf("Index of 30: %d\n\n",
           doubly_list_index_of(d_linked_list, &c, compare_int));


    printf("----- REMOVE TESTS -----\n");
    doubly_list_remove_first(d_linked_list);  // remove 10
    doubly_list_remove_last(d_linked_list);   // remove 30

    printf("List after remove first & last: ");
    print_list(d_linked_list->head);

    doubly_list_remove_at(d_linked_list, 1);  // remove 40

    printf("List after remove_at(1): ");
    print_list(d_linked_list->head);
    printf("\n");


    printf("----- UPDATE -----\n");
    int new_val = 999;
    doubly_list_insert_last(d_linked_list, &e, sizeof(int));  // add 50
    doubly_list_update(d_linked_list, &e, &new_val, sizeof(int), compare_int);

    printf("List after update 50->999: ");
    print_list(d_linked_list->head);
    printf("\n");


    printf("----- CLONE -----\n");
    doubly_linked_list *clone = doubly_linked_list_init();
    doubly_list_clone(clone, d_linked_list, sizeof(int));

    printf("Cloned list: ");
    print_list(clone->head);
    printf("\n");


    printf("----- REVERSE -----\n");
    doubly_list_reverse(d_linked_list);

    printf("Reversed list: ");
    print_list(d_linked_list->head);
    printf("\n");


    printf("----- APPEND -----\n");
    doubly_list_append(d_linked_list, clone);

    printf("After append: ");
    print_list(d_linked_list->head);
    printf("\n");


    printf("----- CLEAR -----\n");
    doubly_list_clear(&d_linked_list);
    printf("List cleared.\n");

    return 0;
}
