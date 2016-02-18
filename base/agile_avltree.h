#ifndef agile_avltree_header
#define agile_avltree_header

#include "agile_bitree.h"

#define AVL_LFT_HEAVY 1
#define AVL_BALANCED 0
#define AVL_RGT_HEAVY -1

typedef struct agile_avltree_node_ {
	void* data;
	int hidden;
	int factor;
} agile_avltree_node;

typedef agile_bitree agile_avltree;

void agile_avltree_init(agile_avltree* tree, int (*compare)(const void*,const void*), void (*destroy)(void*));
void agile_avltree_destroy(agile_avltree* tree);
int agile_avltree_insert(agile_avltree* tree, const void* data);
int agile_avltree_remove(agile_avltree* tree, const void* data);
int agile_avltree_lookup(agile_avltree* tree, void** data);

#define agile_avltree_size(tree) ((tree)->size)

void test_agile_avltree();

#endif
