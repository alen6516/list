
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "src/list.c"


#define test(fn) \
	puts(".. \x1b[22m" # fn "\x1b[0m"); \
	test_##fn();

static int freeProxyCalls = 0;

void freeProxy(void *val) {
    ++freeProxyCalls;
    free(val);
}

typedef struct {
    char *name;
} User;

static int User_equal(User *a, User *b) {
    return 0 == strcmp(a->name, b->name);
}

// Tests
static void test_list_node_new() {
    char *val = "some value";
    list_node_t *node = list_node_new(val);
    assert(node->val == val);
    free(node);
}

static void test_list_push() {
    // Setup
    list_t *list = list_new();
    list_node_t *a = list_node_new("a");
    list_node_t *b = list_node_new("b");
    list_node_t *c = list_node_new("c");

    // a b c
    list_push(list, a);
    list_push(list, b);
    list_push(list, c);

    // Assertions
    assert(a == list->head);
    assert(c == list->tail);
    assert(3 == list->len);
    assert(b == a->next);
    assert(c == b->next);
    assert(NULL == c->next);

    list_destroy(list);
}

static void test_list_at() {
    // Setup
    list_t *list = list_new();
    list_node_t *a = list_node_new("a");
    list_node_t *b = list_node_new("b");
    list_node_t *c = list_node_new("c");

    // a b c
    list_push(list, a);
    list_push(list, b);
    list_push(list, c);

    // Assertions
    assert(a == list_at(list, 0));
    assert(b == list_at(list, 1));
    assert(c == list_at(list, 2));
    assert(NULL == list_at(list, 3));

    list_destroy(list);
}

static void test_list_destroy() {
    // Setup
    list_t *a = list_new();
    list_destroy(a);

    // a b c
    list_t *b = list_new();
    list_push(b, list_node_new("a"));
    list_push(b, list_node_new("b"));
    list_push(b, list_node_new("c"));

    list_destroy(b);

    // Assertions
    list_t *c = list_new();
    c->free = freeProxy;
    list_push(c, list_node_new(list_node_new("a")));
    list_push(c, list_node_new(list_node_new("b")));
    list_push(c, list_node_new(list_node_new("c")));
    list_destroy(c);
    assert(3 == freeProxyCalls);
}

static void test_list_find() {
    // Setup
    list_t *langs = list_new();
    list_node_t *js = list_push(langs, list_node_new("js"));
    list_node_t *ruby = list_push(langs, list_node_new("ruby"));

    list_t *users = list_new();
    users->match = User_equal;
    User userTJ = {"tj"};
    User userSimon = {"simon"};
    User userTaylor = {"taylor"};
    list_node_t *tj = list_push(users, list_node_new(&userTJ));
    list_node_t *simon = list_push(users, list_node_new(&userSimon));

    // Assertions
    list_node_t *a = list_find(langs, "js");
    list_node_t *b = list_find(langs, "ruby");
    list_node_t *c = list_find(langs, "foo");
    assert(js == a);
    assert(ruby == b);
    assert(NULL == c);

    list_destroy(langs);

    a = list_find(users, &userTJ);
    b = list_find(users, &userSimon);
    c = list_find(users, &userTaylor);
    assert(tj == a);
    assert(simon == b);
    assert(NULL == c);

    list_destroy(users);
}

static void test_list_iterator() {
    // Setup
    list_t *list = list_new();
    list_node_t *tj = list_node_new("tj");
    list_node_t *taylor = list_node_new("taylor");
    list_node_t *simon = list_node_new("simon");

    // tj taylor simon
    list_push(list, tj);
    list_push(list, taylor);
    list_push(list, simon);

    // From head
    list_iterator_t *it = list_iterator_new(list);
    list_node_t *a = list_iterator_next(it);
    list_node_t *b = list_iterator_next(it);
    list_node_t *c = list_iterator_next(it);
    list_node_t *d = list_iterator_next(it);

    // Assertions
    assert(a == tj);
    assert(b == taylor);
    assert(c == simon);
    assert(NULL == d);
    
    list_iterator_destroy(it);

    list_destroy(list);
}

int main() {
	printf("\nlist_t: %ld\n", sizeof(list_t));
  	printf("list_node_t: %ld\n", sizeof(list_node_t));
 	printf("list_iterator_t: %ld\n\n", sizeof(list_iterator_t));
 	
	test(list_node_new);
 	test(list_push);
 	test(list_find);
 	test(list_at);
 	test(list_destroy);
 	test(list_iterator_t);
 	puts("... \x1b[32m100%\x1b[0m\n");
 	return 0;
}
