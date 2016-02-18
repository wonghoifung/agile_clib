#include <string.h>
#include "agile_avltree.h"

static void destroy_right(agile_avltree* tree, agile_bitree_node* node);

static void rotate_left(agile_bitree_node** node) {

}

static void rotate_right(agile_bitree_node** node) {

}

static void destroy_left(agile_avltree* tree, agile_bitree_node* node) {

}

static void destroy_right(agile_avltree* tree, agile_bitree_node* node) {

}

static int insert(agile_avltree* tree, agile_bitree_node** node, const void* data, int* balanced) {

	return 0;
}

static int hide(agile_avltree* tree, agile_bitree_node* node, const void* data) {
	int cmpval, retval;

	return retval;
}

static int lookup(agile_avltree* tree, agile_bitree_node* node, void** data) {
	int cmpval, retval;

	return retval;
}

void agile_avltree_init(agile_avltree* tree, int (*compare)(const void*,const void*), void (*destroy)(void*)) {
	agile_bitree_init(tree, destroy);
	tree->compare = compare;
}

void agile_avltree_destroy(agile_avltree* tree) {
	destroy_left(tree, NULL);
	memset(tree, 0, sizeof(agile_avltree));
}

int agile_avltree_insert(agile_avltree* tree, const void* data) {
	int balanced = 0;
	return insert(tree, &agile_bitree_root(tree), data, &balanced);
}

int agile_avltree_remove(agile_avltree* tree, const void* data) {
	return hide(tree, agile_bitree_root(tree), data);
}

int agile_avltree_lookup(agile_avltree* tree, void** data) {
	return lookup(tree, agile_bitree_root(tree), data);
}

//////////////////////////////

#include "test_common.h"

void test_agile_avltree() {

}
