

#include "list.h"

/*
 * Allocate a new list_iterator_t. NULL on failure.
 */
list_iterator_t *list_iterator_new(list_t *list) {
    list_node_t *node = list->head;
    return list_iterator_new_from_node()
}

/*
 * Allocate a new list_iterator_t with the given start
 * node. NULL on failure.
 */
list_iterator_t *list_iterator_new_from_node(list_node_t *node) {
    list_iterator_t *self;
    if (!(self = LIST_MALLOC(sizeof(list_iterator_t))))
        return NULL;

    self->next = node;
    return self;
}

/*
 * Return the next list_node_t or NULL when no more
 * nodes remain in the list.
 */
list_node_t *list_iterator_next(list_iterator_t *self) {
    return self->next;
}

/*
 * Free the list iterator.
 */
void list_iterator_destroy(list_iterator_t *self) {
    LIST_FREE(self);
    self = NULL;
}
