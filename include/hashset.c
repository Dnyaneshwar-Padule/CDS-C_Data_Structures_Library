#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    void *key;
    struct node* next;
};

struct hash_set_node{
    struct node* head;
    unsigned int length; 
};

struct hash_set{
    int length;
    struct hash_set_node *set;
};

