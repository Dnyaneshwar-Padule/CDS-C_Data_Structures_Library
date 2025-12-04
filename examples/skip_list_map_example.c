#include<stdio.h>
#include<stdlib.h>
#include "../include/skip_list_map.h"

int compare(const void *a, const void *b){
    int x = *(int*)a;
    int y = *(int*)b;
    return (x > y) - (x < y);
}

void show_skip_list_map(skip_list_map* ordered_map){
    skip_list_map_node *current = ordered_map->head, *next = NULL, *down = NULL;

    while(current){
        down = current->down;
        printf("Level %d:", current->level);
        while (current->next){
            printf("%3d (%3d) --> ", *((int*)current->next->key), *((int*)current->next->value));
            current = current->next;
        }
        printf("NULL\n");
        current = down;
    }
}

int main(){

    //It initialized an empty skip list map
    skip_list_map *ordered_map = skip_list_map_init();

    if(ordered_map == NULL){
        printf("Unable to initialize skip list map\n");
        return 0;
    }

    printf("Skip List Map initialized !\n");

    int key = 10;
    int value = 100;

    //Adding key-value pairs in skip list map
    
    printf("Adding values \n");
    for(int i = 1; i <= 6; ++i){
        printf("%d - %d : %s\n", key, value, skip_list_map_put(ordered_map, &key, sizeof(key), &value, sizeof(value), compare) ? "Added." : "Not added." );
        key++;
        value++;
    }
    printf("-----------------------------------------\n");
    printf("Skip list looks like \n");
    show_skip_list_map(ordered_map);
    printf("-----------------------------------------\n");
    printf("Total pairs : %d\n", ordered_map->size);
    printf("-----------------------------------------\n");


    //Checking keys
    for(int i = 1; i <= 6; ++i){
        printf("%d contains %s\n", key, skip_list_map_contains(ordered_map, &key, compare) ? "YES" : "NO");
        key--;
        value--;
    }
    printf("-----------------------------------------\n");

    //getting values by keys
    for(int i = 0; i <= 6; ++i){
        void *val = skip_list_map_get(ordered_map, &key, compare);

        if(val != NULL){
            printf("Key %d : Value %d\n", key, *((int*)val));
        }
        else{
            printf("Key %d does not exists \n", key);
        }
        key++;
        value++;
    }
    printf("-----------------------------------------\n");

    //Removing pairs
    printf("%d : %s\n", key, skip_list_map_remove(ordered_map, &key, compare) ? "Removed" : "Not Removed" );
    key = 10;
    printf("%d : %s\n", key, skip_list_map_remove(ordered_map, &key, compare) ? "Removed" : "Not Removed" );
    key = 13;
    printf("%d : %s\n", key, skip_list_map_remove(ordered_map, &key, compare) ? "Removed" : "Not Removed" );
    key =  15;
    printf("%d : %s\n", key, skip_list_map_remove(ordered_map, &key, compare) ? "Removed" : "Not Removed" );

    printf("-----------------------------------------\n");
    printf("Skip list looks like \n");
    show_skip_list_map(ordered_map);
    printf("-----------------------------------------\n");

    skip_list_map_clear(&ordered_map);
    printf("Map cleared\n");
    return 0;
}