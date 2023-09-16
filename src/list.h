#ifndef LIST_H_
#define LIST_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ListElmt{
    void *data;
    struct ListElmt *next;
}ListElmt;

typedef struct List{
    ListElmt *head;
    ListElmt *tail;
    void (*destroy)(void *data);
    int size;
}List;

void list_init(List *list, void (*destroy)(void *data));
void list_destroy(List *list);
int list_ins_next(List *list, ListElmt *element, void *data);
int list_rem_next(List *list, ListElmt *element, void **data);

#endif