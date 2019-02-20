

#include "list.h"

/*
 * Allocate a new list_t. NULL on failure.
 */
list_t *list_new() {
    list_t *self;
    if (!(self = LIST_MALLOC(sizeof(list_t))))
        return NULL;

    self->head = NULL;
    self->tail = NULL;
    self->len = 0;
    self->free = NULL;
    self->match = NULL;
    return self;
}

/*
 * Free the list.
 */
void list_destroy(list_t *self) {
    unsigned int len = self->len;
    list_node_t *next;
    list_node_t *curr = self->head;

    while(len--) {
        next = curr->next;
        if (self->free)
            self->free(curr->val);
        LIST_FREE(curr);
        curr = next;
    }

    LIST_FREE(self);
}

/*
 * Append the given node to the list
 * and return the node. NULL on failure.
 */
list_node_t *list_push(list_t *self, list_node_t *node) {
    if (!node) return NULL;

    if (self->len) {
        node->next = NULL;
        self->tail->next = node;
        self->tail = node;
    } else {
        self->head = self->tail = node;
        node->next = NULL;
    }

    ++self->len;
    return node;
}

/*
 * Return / detch the last node in the list, or NULL.
 */
list_node_t *list_pop(list_t *self) {
    if (!self->len) return NULL;

    // unable without prev

}

/*
 * Return the node associated to val or NULL.
 */
list_node_t *list_find(list_t *self, void *val) {
    list_iterator_t *it = list_iterator_new(self);
    list_node_t *node;

    while ((node = list_iterator_next(it))) {
        if (self->match) {
            if (self->match(val, node->val)) {
                list_iterator_destroy(it);
                return node;
            }
        } else {
            if (val == node->val) {
                list_iterator_destroy(it);
                return node;
            }
        }
    }

    list_iterator_destroy(it);
    return NULL;
}

/*
 * Return the node at the given index or NULL.
 */
list_node_t *list_at(list_t *self, int index) {
    if ((unsigned)index < self->len) {
        list_iterator_t *it = list_iterator_new(self);
        list_node_t *node = list_iterator_next(it);
        while (index--) node = list_iterator_next(it);
        list_iterator_destroy(it);
        return node;
    }

    return NULL;
}

/*
 * Remove the given node from the list, freeing it and it's value.
 */
void list_remove(list_t *self, list_node_t *node) {
    // unable without prev
}
