#include <string.h>
#include <assert.h>
#include "agile_avltree.h"

static void destroy_right(agile_avltree* tree, agile_bitree_node* node);

static void rotate_left(agile_bitree_node** node) {
	agile_bitree_node* left;
	agile_bitree_node* grandchild;
	left = agile_bitree_left(*node);
	if (((agile_avltree_node*)agile_bitree_data(left))->factor == AVL_LFT_HEAVY) {
		// LL rotation
		agile_bitree_left(*node) = agile_bitree_right(left);
		agile_bitree_right(left) = *node;
		((agile_avltree_node*)agile_bitree_data(*node))->factor = AVL_BALANCED;
		((agile_avltree_node*)agile_bitree_data(left))->factor = AVL_BALANCED;
		*node = left;
	} else {
		// LR rotation
		grandchild = agile_bitree_right(left);
		agile_bitree_right(left) = agile_bitree_left(grandchild);
		agile_bitree_left(grandchild) = left;
		agile_bitree_left(*node) = agile_bitree_right(grandchild);
		agile_bitree_right(grandchild) = *node;
		switch (((agile_avltree_node*)agile_bitree_data(grandchild))->factor) {
			case AVL_LFT_HEAVY:
				((agile_avltree_node*)agile_bitree_data(*node))->factor = AVL_RGT_HEAVY;
				((agile_avltree_node*)agile_bitree_data(left))->factor = AVL_BALANCED;
				break;
			case AVL_BALANCED:
				((agile_avltree_node*)agile_bitree_data(*node))->factor = AVL_BALANCED;
				((agile_avltree_node*)agile_bitree_data(left))->factor = AVL_BALANCED;
				break;
			case AVL_RGT_HEAVY:
				((agile_avltree_node*)agile_bitree_data(*node))->factor = AVL_BALANCED;
				((agile_avltree_node*)agile_bitree_data(left))->factor = AVL_LFT_HEAVY;
				break;
			default:
				assert(0);
		}
		((agile_avltree_node*)agile_bitree_data(grandchild))->factor = AVL_BALANCED;
		*node = grandchild;
	}
}

static void rotate_right(agile_bitree_node** node) {
	agile_bitree_node* right;
	agile_bitree_node* grandchild;
	right = agile_bitree_right(*node);
	if (((agile_avltree_node*)agile_bitree_data(right))->factor==AVL_RGT_HEAVY) {
		// RR rotation
		agile_bitree_right(*node) = agile_bitree_left(right);
		agile_bitree_left(right) = *node;
		((agile_avltree_node*)agile_bitree_data(*node))->factor = AVL_BALANCED;
		((agile_avltree_node*)agile_bitree_data(right))->factor = AVL_BALANCED;
		*node = right;
	} else {
		// RL rotation
		grandchild = agile_bitree_left(right);
		agile_bitree_left(right) = agile_bitree_right(grandchild);
		agile_bitree_right(grandchild) = right;
		agile_bitree_right(*node) = agile_bitree_left(grandchild);
		agile_bitree_left(grandchild) = *node;
		switch (((agile_avltree_node*)agile_bitree_data(grandchild))->factor) {
			case AVL_LFT_HEAVY:
				((agile_avltree_node*)agile_bitree_data(*node))->factor = AVL_BALANCED;
				((agile_avltree_node*)agile_bitree_data(right))->factor = AVL_RGT_HEAVY;
				break;
			case AVL_BALANCED:
				((agile_avltree_node*)agile_bitree_data(*node))->factor = AVL_BALANCED;
				((agile_avltree_node*)agile_bitree_data(right))->factor = AVL_BALANCED;
				break;
			case AVL_RGT_HEAVY:
				((agile_avltree_node*)agile_bitree_data(*node))->factor = AVL_LFT_HEAVY;
				((agile_avltree_node*)agile_bitree_data(right))->factor = AVL_BALANCED;
				break;
			default:
				assert(0);
		}
		((agile_avltree_node*)agile_bitree_data(grandchild))->factor = AVL_BALANCED;
		*node = grandchild;
	}
}

static void destroy_left(agile_avltree* tree, agile_bitree_node* node) {
	agile_bitree_node** position;
	if (agile_bitree_size(tree)==0) return;
	if (node = NULL) position = &tree->root;
	else position = &node->left;
	if (*position != NULL) {
		destroy_left(tree, *position);
		destroy_right(tree, *position);
		if (tree->destroy != NULL) {
			tree->destroy(((agile_avltree_node*)(*position)->data)->data); // user data
		}
		free((*position)->data); // avl node
		free(*position); // bitree node
		*position = NULL;
		tree->size -= 1;
	}
}

static void destroy_right(agile_avltree* tree, agile_bitree_node* node) {
	agile_bitree_node** position;
	if (agile_bitree_size(tree)==0) return;
	if (node = NULL) position = &tree->root;
	else position = &node->right;
	if (*position != NULL) {
		destroy_left(tree, *position);
		destroy_right(tree, *position);
		if (tree->destroy != NULL) {
			tree->destroy(((agile_avltree_node*)(*position)->data)->data); // user data
		}
		free((*position)->data); // avl node
		free(*position); // bitree node
		*position = NULL;
		tree->size -= 1;
	}
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
