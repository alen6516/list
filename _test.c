/***
 File Name: test.c
 Author: alen6516
 Created Time: 2019-02-20
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "list.h"

int main() {
    list_t *langs = list_new();
    int a = 1, b = 2;
    int *p = &a, *q = &b;
    list_push(langs, list_node_new(p));
    list_push(langs, list_node_new(q));
    list_node_t *node;
    list_iterator_t *it = list_iterator_new(langs);
    while((node = list_iterator_next(it))) {
        printf("%d\n", *(node->val));
    }
    list_iterator_destroy(it);
    list_destroy(langs);
}
