#include<stdio.h>
#include "../include/skip_list_set.h"

int compare(const void *a, const void *b){
    int x = *(int*)a;
    int y = *(int*)b;
    return (x > y) - (x < y);
}

void print_set(skip_list_set *set){
    skip_list_set_node *current = set->head;

    while (current->down)
        current = current->down;
    
    while (current->next){
        printf("%d -> ", *((int*)current->next->key));
        current = current->next;
    }
    
    printf("NULL \n");
}

int main(){

    //This function creates an empty skip list
    skip_list_set *ordered_set = skip_list_set_init();
    printf("Skip list set initialized \n");

    int val1 = 10;
    int val2 = 20;
    int val3 = 30;
    int val4 = 40;
    int val5 = 50;
    int val6 = 60;

    // Adding values into the skip_list_set
    printf("Adding values\n");
    printf("%d %s\n", val4, skip_list_set_add(ordered_set, &val4, sizeof(int), compare) ? "Added." : "Not added.");
    printf("%d %s\n", val1, skip_list_set_add(ordered_set, &val1, sizeof(int), compare) ? "Added." : "Not added.");
    printf("%d %s\n", val3, skip_list_set_add(ordered_set, &val3, sizeof(int), compare) ? "Added." : "Not added.");
    printf("%d %s\n", val2, skip_list_set_add(ordered_set, &val2, sizeof(int), compare) ? "Added." : "Not added.");
    printf("%d %s\n", val6, skip_list_set_add(ordered_set, &val6, sizeof(int), compare) ? "Added." : "Not added.");
    printf("%d %s\n", val5, skip_list_set_add(ordered_set, &val5, sizeof(int), compare) ? "Added." : "Not added.");
    printf("%d %s\n", val1, skip_list_set_add(ordered_set, &val1, sizeof(int), compare) ? "Added." : "Not added.");
    printf("%d %s\n", val2, skip_list_set_add(ordered_set, &val2, sizeof(int), compare) ? "Added." : "Not added.");
    printf("---------------------\n");
    
    printf("Set Looks like : ");
    print_set(ordered_set);

    printf("---------------------\n");
    printf("Total elements : %d\n", ordered_set->size);
    printf("---------------------\n");
    
    //Checking values exists or not
    printf("%d contains : %s\n", val1, skip_list_set_contains(ordered_set, &val1, compare) ? "YES" : "NO");
    printf("%d contains : %s\n", val2, skip_list_set_contains(ordered_set, &val2, compare) ? "YES" : "NO");
    printf("%d contains : %s\n", val3, skip_list_set_contains(ordered_set, &val3, compare) ? "YES" : "NO");
    printf("%d contains : %s\n", val4, skip_list_set_contains(ordered_set, &val4, compare) ? "YES" : "NO");
    printf("%d contains : %s\n", val5, skip_list_set_contains(ordered_set, &val5, compare) ? "YES" : "NO");
    printf("%d contains : %s\n", val6, skip_list_set_contains(ordered_set, &val6, compare) ? "YES" : "NO");
    printf("---------------------\n");
    
    //Removing values
    printf("Removing %d : %s\n", val1, skip_list_set_remove(ordered_set, &val1, compare) ? "Removed" : "Not removed");
    printf("Removing %d : %s\n", val3, skip_list_set_remove(ordered_set, &val3, compare) ? "Removed" : "Not removed");
    printf("Removing %d : %s\n", val5, skip_list_set_remove(ordered_set, &val5, compare) ? "Removed" : "Not removed");
    
    val6 = 8;
    printf("Removing %d : %s\n", val6, skip_list_set_remove(ordered_set, &val6, compare) ? "Removed" : "Not removed");
    printf("---------------------\n");
    
    printf("Set Looks like : ");
    print_set(ordered_set);
    
    printf("---------------------\n");
    //clearing skip_list_set
    skip_list_set_clear(&ordered_set);
    printf("Skip List set cleared !\n");

    return 0;
}