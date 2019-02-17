#ifndef LIST_H
#define LIST_H

#include <stdio.h>

// Version
#define LIST_VERSION "0.0.1"

// Memory management macros
#ifndef LIST_MALLOC
#define LIST_MALLOC malloc
#endif

// list_t node struct
typedef struct list_node {
    struct list_node *next;
    int *val;
} list_node_t;

// list_t struct
typedef struct {
    list_node_t *head;
    unsigned int len;
    void (*free)(int *val);
    int (*match)(int *a, int *b);
} list_t;

// list_t iterator struct
typedef struct {
    list_node_t *next;
} list_iterator_t;

// Node prototypes
list_node_t *list_node_new(int *val);

// list_t prototypes
list_t *list_new();

list_node_t *list_push(list_t *self, list_node_t *node);

list_node_t *list_find(list_t *self, int *val);

list_node_t *list_at(list_t *self, int index);

list_node_t *list_pop(list_t *self);

void list_remove(list_t *self, list_node_t *node);

void list_destroy(list_t *self);

// list iterator prototypes
list_iterator_t *list_iterator_new(list_t *list);

list_iterator_t *list_iterator_new_from_node(list_node_t *node);

list_node_t *list_iterator_next(list_iterator_t *self);

void list_iterator_next(list_iterator_t *self);

void list_iterator_destroy(list_iterator_t *self);

#endif  /* LIST_H */
