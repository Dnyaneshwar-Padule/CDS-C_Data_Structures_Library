#include<stdio.h>
#include<stdlib.h>
#include "../include/hash_set.h"

int compare(const void *a, const void *b) {
    int x = *(int*)a;
    int y = *(int*)b;
    if (x == y) return 0;
    return (x < y) ? -1 : 1;
}

unsigned int hash(const void *key, int len){
    return *((int*)key) % len;
}

int main(){

    //It creates a empty hash set with capacity of 3
    hash_set *set = hash_set_init(3);

    
    if(set){
        printf("Hash set created, initial length : %d\n", set->length);
    }
    else{
        printf("Hash set not created !\n");
        return 0;
    }

    int key1 = 1;
    int key2 = 2;
    int key3 = 3;
    int key4 = 4;
    int key5 = 5;
    int key6 = 6;
    int key7 = 7;
    int temp = 100;

    // Putting keys (elements)
    hash_set_add(set, &key1, sizeof(int), hash, compare);
    hash_set_add(set, &key2, sizeof(int), hash, compare);
    hash_set_add(set, &key3, sizeof(int), hash, compare);
    hash_set_add(set, &key4, sizeof(int), hash, compare);
    hash_set_add(set, &key5, sizeof(int), hash, compare);
    hash_set_add(set, &key6, sizeof(int), hash, compare);
    hash_set_add(set, &key7, sizeof(int), hash, compare);
    hash_set_add(set, &key7, sizeof(int), hash, compare);

    printf("All keys are inserted\n");
    printf("No. of hash set nodes : %d\n", set->length);

    for(int i = 0; i < set->length; i++)
        printf("%d | ", set->set[i].length);
    printf("\n");


    // Checking if gives elements exists in the hash set
    printf("%d Consists : %s\n",key1, hash_set_contains(set, &key1, hash, compare) ? "YES" : "NO"  );
    printf("%d Consists : %s\n",key2, hash_set_contains(set, &key2, hash, compare) ? "YES" : "NO"  );
    printf("%d Consists : %s\n",key3, hash_set_contains(set, &key3, hash, compare) ? "YES" : "NO"  );
    printf("%d Consists : %s\n",key4, hash_set_contains(set, &key4, hash, compare) ? "YES" : "NO"  );
    printf("%d Consists : %s\n",key5, hash_set_contains(set, &key5, hash, compare) ? "YES" : "NO"  );
    printf("%d Consists : %s\n",key6, hash_set_contains(set, &key6, hash, compare) ? "YES" : "NO"  );
    printf("%d Consists : %s\n",key7, hash_set_contains(set, &key7, hash, compare) ? "YES" : "NO"  );
    printf("%d Consists : %s\n",temp, hash_set_contains(set, &temp, hash, compare) ? "YES" : "NO"  );
    
    
    //removing elements from hash set
    printf("Remove %d\n", key1, hash_set_remove(set, &key1, hash, compare));
    printf("Remove %d\n", key3, hash_set_remove(set, &key3, hash, compare));
    printf("Remove %d\n", key5, hash_set_remove(set, &key5, hash, compare));
    
    printf("%d Consists : %s\n",key1, hash_set_contains(set, &key1, hash, compare) ? "YES" : "NO"  );
    printf("%d Consists : %s\n",key3, hash_set_contains(set, &key3, hash, compare) ? "YES" : "NO"  );
    printf("%d Consists : %s\n",key5, hash_set_contains(set, &key5, hash, compare) ? "YES" : "NO"  );
    
    for(int i = 0; i < set->length; i++)
        printf("%d | ", set->set[i].length);
    printf("\n");

    hash_set_clear(&set);
    printf("Hash set cleared !\n");
    return 0;
}