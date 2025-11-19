#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/stack.h"   // adjust path ,if needed

typedef struct {
    int id;
    char name[20];
} Employee;

int compare_emp(const void *a, const void *b) {
    const Employee *e1 = a;
    const Employee *e2 = b;
    return e1->id - e2->id;
}

int main() {

    stack s;
    init(&s);

    Employee e;

    printf("Pushing Employees...\n");

    e.id = 101; strcpy(e.name, "Rahul");
    stack_push(&s, &e, sizeof(Employee));

    e.id = 102; strcpy(e.name, "Mahesh");
    stack_push(&s, &e, sizeof(Employee));

    e.id = 103; strcpy(e.name, "Suresh");
    stack_push(&s, &e, sizeof(Employee));

    printf("Current stack length: %u\n", stack_length(&s));
    
    Employee *p = stack_peek(&s);
    printf("Peek: %d | %s\n", p->id, p->name);
    

    // Search test
    Employee x;
    x.id = 102;
    int index = stack_search(&s, &x, compare_emp);
    printf("Search(102) index: %d\n", index);

    printf("\nPopping elements...\n");

    p = stack_pop(&s);
    if(p) {
        printf("Popped: %d | %s\n", p->id, p->name);
        // user frees popped data if needed
        free(p);
    }

    p = stack_pop(&s);
    if(p) {
        printf("Popped: %d | %s\n", p->id, p->name);
        free(p);
    }

    printf("Current stack length: %u\n", stack_length(&s));

    printf("\nClearing stack...\n");
    stack_clear(&s);

    if(stack_is_empty(&s))
        printf("Stack cleared successfully!\n");

    return 0;
}
