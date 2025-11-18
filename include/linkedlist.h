#define NEWNODE() ((struct list_node*)malloc(sizeof(struct list_node)))

struct list_node{
    void *data;
    struct list_node *next;
};

typedef struct list_node list_node;

list_node* list_insert(list_node* head, const void *data, size_t size);
list_node* list_insert_first(list_node* head, const void* data, size_t size);
list_node* list_insert_last(list_node* head, const void *data, size_t size );
list_node* list_insert_at(list_node* head, const void* data, size_t size, unsigned int index);

list_node* list_get_node(list_node* head, unsigned const int index);
void* list_first(list_node* head);
void* list_last(list_node *head);
void* list_get(list_node *head, unsigned const int index);
int list_index_of(list_node* head, const void *data, int (*compare)(const void*, const void*));
int list_last_index_of(list_node* head, const void *data, int (*compare)(const void*, const void*));
int list_contains(list_node* head, const void *data, int (*compare)(const void*, const void*));

list_node* list_remove_first(list_node *head);
list_node* list_remove_last(list_node* head);
list_node* list_remove_at(list_node* head, unsigned const int index);
list_node* list_remove_value(list_node* head, const void *value, int (*compare)(const void*, const void*));

list_node* list_update(list_node* head, const void *old_data, const void *new_data, size_t size, int (*compare)(const void*, const void*) );
list_node* list_reverse(list_node* head);
list_node* list_clone(list_node* head, size_t size);
list_node* list_append(list_node* head1, list_node* head2);
void list_clear(list_node * head);
unsigned int list_length(list_node* head);


/*
int compare_id(const void *e1, const void* e2){
    Employee *emp1 = (Employee*)e1;
    Employee *emp2 = (Employee*)e2;
    
    return emp1->id - emp2->id;
}

int compare_name(const void *e1, const void* e2){
    Employee *emp1 = (Employee*)e1;
    Employee *emp2 = (Employee*)e2;
    
    return strcmp(emp1->name, emp2->name);
}

int main(){
    Employee e;
    Employee *p;
    list_node* head = NULL;
    
    e.id = 101;
    strcpy(e.name, "Rahul");
    head = insert(head, &e, sizeof(Employee));
    
    e.id = 102;
    strcpy(e.name, "Mahesh");
    head = insert(head, &e, sizeof(Employee));
    
    e.id = 103;
    strcpy(e.name, "Yogesh");
    head = insert_at(head, &e, sizeof(Employee), 2);
    
    e.id = 104;
    strcpy(e.name, "Ram");
    head = add_last(head, &e, sizeof(Employee));
    
    e.id = 105;
    strcpy(e.name, "Suresh");
    head = add_first(head, &e, sizeof(Employee));
    
    int len = llength(head);
    printf("Total Employees : %d\n", len);
    
    list_node* temp = head;
    while(temp){
        p = temp->data;
        printf("%d | %s \n", p->id, p->name);
        temp = temp->next;
    }
    
    p = get_first(head);
    printf("\n%d | %s \n", p->id, p->name);
    
    p = get_last(head);
    printf("\n%d | %s \n", p->id, p->name);

    int i = index_of(head, p, compare_id);
    printf("\nIndex of last : %d\n", i);
    
    head = reverse_list(head);
    temp = head;
    printf("\n");
    while(temp){
        p = temp->data;
        printf("%d | %s \n", p->id, p->name);
        temp = temp->next;
    }
    
    head = delete_first(head);
    temp = head;
    printf("\n");
    while(temp){
        p = temp->data;
        printf("%d | %s \n", p->id, p->name);
        temp = temp->next;
    }
    
    head = delete_last(head);
    temp = head;
    printf("\n");
    while(temp){
        p = temp->data;
        printf("%d | %s \n", p->id, p->name);
        temp = temp->next;
    }
    
    head = delete_at_index(head, 2);
    temp = head;
    printf("\n");
    while(temp){
        p = temp->data;
        printf("%d | %s \n", p->id, p->name);
        temp = temp->next;
    }
    
    clear(head);
    return 0;
}

*/