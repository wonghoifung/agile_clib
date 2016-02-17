#ifndef agile_bitree_header
#define agile_bitree_header

#include <stdlib.h>

typedef struct agile_bitree_node_ {
	void* data;
	struct agile_bitree_node_* left;
	struct agile_bitree_node_* right;
} agile_bitree_node;

typedef struct agile_bitree_ {
	int size;
	int (*compare)(const void* key1, const void* key2);
	void (*destroy)(void* data);
	agile_bitree_node* root;
} agile_bitree;

void agile_bitree_init(agile_bitree* tree, void(*destroy)(void*));
void agile_bitree_destroy(agile_bitree* tree);
int agile_bitree_ins_left(agile_bitree* tree, agile_bitree_node* node, const void* data);
int agile_bitree_ins_right(agile_bitree* tree, agile_bitree_node* node, const void* data);
void agile_bitree_rem_left(agile_bitree* tree, agile_bitree_node* node);
void agile_bitree_rem_right(agile_bitree* tree, agile_bitree_node* node);
int agile_bitree_merge(agile_bitree* merge, agile_bitree* left, agile_bitree* right, const void* data);

#define agile_bitree_size(tree) ((tree)->size)
#define agile_bitree_root(tree) ((tree)->root)
#define agile_bitree_is_eob(node) ((node)==NULL)
#define agile_bitree_is_leaf(node) ((node)->left==NULL && (node)->right==NULL)
#define agile_bitree_data(node) ((node)->data)
#define agile_bitree_left(node) ((node)->left)
#define agile_bitree_right(node) ((node)->right)

void test_agile_bitree();

#endif
