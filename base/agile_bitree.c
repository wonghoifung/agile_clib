#include <string.h>
#include "agile_bitree.h"

void agile_bitree_init(agile_bitree* tree, void(*destroy)(void*)) {
	tree->size = 0;
	tree->destroy = destroy;
	tree->root = NULL;
}

void agile_bitree_destroy(agile_bitree* tree) {
	agile_bitree_rem_left(tree, NULL);
	memset(tree, 0, sizeof(agile_bitree));
}

int agile_bitree_ins_left(agile_bitree* tree, agile_bitree_node* node, const void* data) {
	agile_bitree_node* new_node;
	agile_bitree_node** position;
	if (node == NULL) {
		if (agile_bitree_size(tree) > 0) return -1;
		position = &tree->root;
	} else {
		if (agile_bitree_left(node) != NULL) return -1;
		position = &node->left;
	}
	if ((new_node=(agile_bitree_node*)malloc(sizeof(agile_bitree_node)))==NULL) return -1;
	new_node->data = (void*)data;
	new_node->left = NULL;
	new_node->right = NULL;
	*position = new_node;
	tree->size += 1;
	return 0;
}

int agile_bitree_ins_right(agile_bitree* tree, agile_bitree_node* node, const void* data) {
	agile_bitree_node* new_node;
	agile_bitree_node** position;
	if (node == NULL) {
		if (agile_bitree_size(tree) > 0) return -1;
		position = &tree->root;
	} else {
		if (agile_bitree_right(node) != NULL) return -1;
		position = &node->right;
	}
	if ((new_node=(agile_bitree_node*)malloc(sizeof(agile_bitree_node)))==NULL) return -1;
	new_node->data = (void*)data;
	new_node->left = NULL;
	new_node->right = NULL;
	*position = new_node;
	tree->size += 1;
	return 0;
}

void agile_bitree_rem_left(agile_bitree* tree, agile_bitree_node* node) {
	agile_bitree_node** position;
	if (agile_bitree_size(tree)==0) {
		return;
	}
	if (node==NULL) position = &tree->root;
	else position = &node->left;
	if (*position!=NULL) {
		agile_bitree_rem_left(tree, *position);
		agile_bitree_rem_right(tree, *position);
		if (tree->destroy!=NULL) {
			tree->destroy((*position)->data);
		}
		free(*position);
		*position = NULL;
		tree->size -= 1;
	}
}

void agile_bitree_rem_right(agile_bitree* tree, agile_bitree_node* node) {
	agile_bitree_node** position;
	if (agile_bitree_size(tree)==0) {
		return;
	}
	if (node==NULL) position = &tree->root;
	else position = &node->right;
	if (*position!=NULL) {
		agile_bitree_rem_left(tree, *position);
		agile_bitree_rem_right(tree, *position);
		if (tree->destroy!=NULL) {
			tree->destroy((*position)->data);
		}
		free(*position);
		*position = NULL;
		tree->size -= 1;
	}
}

int agile_bitree_merge(agile_bitree* merge, agile_bitree* left, agile_bitree* right, const void* data) {
	agile_bitree_init(merge, left->destroy);
	if (agile_bitree_ins_left(merge, NULL, data)!=0) {
		agile_bitree_destroy(merge);
		return -1;
	}
	agile_bitree_root(merge)->left = agile_bitree_root(left);
	agile_bitree_root(merge)->right = agile_bitree_root(right);
	merge->size = merge->size + agile_bitree_size(left) + agile_bitree_size(right);
	left->root = NULL;
	left->size = 0;
	right->root = NULL;
	right->size = 0;
	return 0;
}

//////////////////////////////

#include "test_common.h"
#include "agile_queue.h"

void print_bitree(agile_bitree* tree) {
	agile_bitree_node* node = tree->root;
	agile_queue queue;
	agile_queue_init(&queue, NULL);
	agile_queue_enqueue(&queue, node);
	while (agile_queue_size(&queue) > 0) {
		int cnt = agile_queue_size(&queue);
		int i=0;
		for (;i<cnt;++i) {
			void* data;
			void* l;
			void* r;
			agile_queue_dequeue(&queue, &data);
			printf("%s ", (char*)agile_bitree_data((agile_bitree_node*)data));
			l = ((agile_bitree_node*)data)->left;
			r = ((agile_bitree_node*)data)->right;
			if (l != NULL) agile_queue_enqueue(&queue, l);
			if (r != NULL) agile_queue_enqueue(&queue, r);
		}
		printf("\n");
	}
	agile_queue_destroy(&queue);
}

void test_agile_bitree() {
	agile_bitree tree;
	agile_bitree_init(&tree, free);
	char* d1 = get_data(1);
	char* d2 = get_data(2);
	char* d3 = get_data(3);
	char* d4 = get_data(4);
	agile_bitree_ins_left(&tree, NULL, d1);
	agile_bitree_ins_left(&tree, agile_bitree_root(&tree), d2);
	agile_bitree_ins_right(&tree, agile_bitree_root(&tree), d3);
	agile_bitree_ins_left(&tree, agile_bitree_root(&tree)->left, d4);
	print_bitree(&tree);
	printf("\n");
	agile_bitree_rem_left(&tree, agile_bitree_root(&tree));
	print_bitree(&tree);
	agile_bitree_destroy(&tree);
}
