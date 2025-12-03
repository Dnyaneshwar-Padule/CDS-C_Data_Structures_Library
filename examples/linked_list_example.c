#include <stdio.h>
#include <string.h>
#include "../include/linked_list.h"

// Compare function for integers
int compare_int(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return (x > y) - (x < y);   // returns 1, 0, -1
}

int main() {
    linked_list *l_list = list_init();
    int length;

    int a = 10, b = 20, c = 30, d = 40, e = 50;

    printf("----- INSERT TESTS -----\n");
    list_insert_first(l_list, &a, sizeof(int));   // 10
    list_insert_last(l_list,  &b, sizeof(int));   // 10 -> 20
    list_insert_last(l_list,  &c, sizeof(int));   // 10 -> 20 -> 30
    list_insert_at(l_list,    &d, sizeof(int), 2); // 10 -> 40 -> 20 -> 30

    printf("List after inserts: ");
    length = list_length(l_list);
    for(int i = 1; i <= length; i++){
        printf("%d ", *(int*)list_get(l_list, i));
    }
    printf("\n\n");


    printf("----- GET TESTS -----\n");
    printf("First element: %d\n", *(int*)list_first(l_list));
    printf("Last element:  %d\n", *(int*)list_last(l_list));
    printf("Element at 2:  %d\n", *(int*)list_get(l_list, 2));
    printf("\n");


    printf("----- LENGTH TEST -----\n");
    printf("Length: %u\n\n", list_length(l_list));


    printf("----- CONTAINS / INDEX TEST -----\n");
    printf("Contains 20? %s\n", list_contains(l_list, &b, compare_int) ? "YES" : "NO");
    printf("Index of 30: %d\n\n", list_index_of(l_list, &c, compare_int));


    printf("----- REMOVE TESTS -----\n");
    list_remove_first(l_list);  // remove 10
    list_remove_last(l_list);   // remove 30

    printf("List after remove first & last: ");
    length = list_length(l_list);
    for(int i = 1; i <= length; i++){
        printf("%d ", *(int*)list_get(l_list, i));
    }
    printf("\n");

    list_remove_at(l_list, 1);  // remove index 1 (40)

    printf("List after remove_at(1): ");
    length = list_length(l_list);
    for(int i = 1; i <= length; i++){
        printf("%d ", *(int*)list_get(l_list, i));
    }
    printf("\n\n");


    printf("----- UPDATE -----\n");
    int new_val = 999;
    list_insert_last(l_list, &e, sizeof(int));  // add 50
    list_update(l_list, &e, &new_val, sizeof(int), compare_int);

    printf("List after update 50->999: ");
    length = list_length(l_list);
    for(int i = 1; i <= length; i++){
        printf("%d ", *(int*)list_get(l_list, i));
    }
    printf("\n\n");


    printf("----- CLONE -----\n");
    linked_list *clone = list_init();
    list_clone(clone, l_list,sizeof(int));

    printf("Cloned list: ");
    length = list_length(clone);
    for(int i = 1; i <= length; i++){
        printf("%d ", *(int*)list_get(clone, i));
    }
    printf("\n\n");


    printf("----- REVERSE -----\n");
    list_reverse(l_list);

    printf("Reversed list: ");
    length = list_length(l_list);
    for(int i = 1; i <= length; i++){
        printf("%d ", *(int*)list_get(l_list, i));
    }
    printf("\n\n");


    printf("----- APPEND -----\n");
    list_append(l_list, clone);   // append cloned list

    printf("After append: ");
    length = list_length(l_list);
    for(int i = 1; i <= length ; i++){
        printf("%d ", *(int*)list_get(l_list, i));
    }
    printf("\n\n");


    printf("----- CLEAR -----\n");
    list_clear(&l_list);
    printf("List cleared.\n");

    return 0;
}
