#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../include/hashtable.h"


unsigned int hash(const void *key, int len){
    return *((int*)key) % len;
}

int compare(const void *a, const void *b){
    int x = *(int*)a;
    int y = *(int*)b;
    return (x > y) - (x < y);
}

int main(){
    hash_table *ht = hash_table_init(5);
    int key = 121;
    int value = 1;

    hash_table_put(ht, &key, sizeof(int), &value, sizeof(int), hash, compare);
    key++; value ++;
    hash_table_put(ht, &key, sizeof(int), &value, sizeof(int), hash,compare);
    key++; value ++;
    hash_table_put(ht, &key, sizeof(int), &value, sizeof(int), hash, compare);
    key++; value ++;
    hash_table_put(ht, &key, sizeof(int), &value, sizeof(int), hash, compare);
    key++; value ++;
    hash_table_put(ht, &key, sizeof(int), &value, sizeof(int), hash, compare);
    key = 130 ; value = 130;
    hash_table_put(ht, &key, sizeof(int), &value, sizeof(int), hash, compare);
    
    printf("Length\n");
    for(int i = 0; i < ht->length; i++){
        printf("%d | ", ht->table[i].length);
    }printf("\n");

    int *val = NULL;
    key = 121;
    val = (int*) hash_table_get(ht, &key, hash, compare);
    if( val == NULL){
        printf("key %d not found !\n", key);
    }
    else{
        printf("key %d | value %d\n", key, *val);
    }

    key = 123;
    val = (int*) hash_table_get(ht, &key, hash, compare);
    if( val == NULL){
        printf("key %d not found !\n", key);
    }
    else{
        printf("key %d | value %d\n", key, *val);
    }

    key = 125;
    val = (int*) hash_table_get(ht, &key, hash, compare);
    if( val == NULL){
        printf("key %d not found !\n", key);
    }
    else{
        printf("key %d | value %d\n", key, *val);
    }

    key = 155;
    val = (int*) hash_table_get(ht, &key, hash, compare);
    if( val == NULL){
        printf("key %d not found !\n", key);
    }
    else{
        printf("key %d | value %d\n", key, *val);
    }

    key = 130;
    val = (int*) hash_table_get(ht, &key, hash, compare);
    if( val == NULL){
        printf("key %d not found !\n", key);
    }
    else{
        printf("key %d | value %d\n", key, *val);
    }

    key = 125;
    value = 125;
    hash_table_put(ht, &key, sizeof(int), &value, sizeof(int), hash, compare);

    val = (int*) hash_table_get(ht, &key, hash, compare);
    if( val == NULL){
        printf("key %d not found !\n", key);
    }
    else{
        printf("key %d | value %d\n", key, *val);
    }

    key = 130;
    printf("Key 130 : %d\n", hash_table_contains_key(ht, &key, hash, compare));

    key = 121;
    printf("Key 121 : %d\n", hash_table_contains_key(ht, &key, hash, compare));

    key = 120;
    printf("Key 120 : %d\n", hash_table_contains_key(ht, &key, hash, compare));

    key = 130;
    if(  hash_table_remove(ht, &key, hash, compare) ){
        printf("key %d is removed !\n", key);
    }
    else{
        printf("key %d not found !\n", key);
    }

    key = 130;
    if(  hash_table_remove(ht, &key, hash, compare) ){
        printf("key %d is removed !\n", key);
    }
    else{
        printf("key %d not found !\n", key);
    }

    key = 125;
    if(  hash_table_remove(ht, &key, hash, compare) ){
        printf("key %d is removed !\n", key);
    }
    else{
        printf("key %d not found !\n", key);
    }

    key = 121;
    if(  hash_table_remove(ht, &key, hash, compare) ){
        printf("key %d is removed !\n", key);
    }
    else{
        printf("key %d not found !\n", key);
    }

     printf("Length\n");
    for(int i = 0; i < ht->length; i++){
        printf("%d | ", ht->table[i].length);
    }printf("\n");

    hash_table_clear(ht);
    printf("Hash table cleared...\n");
    return 0;
}