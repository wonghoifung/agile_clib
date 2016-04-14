// 1. every node is either red or black
// 2. root is black
// 3. null leaf(sentinel) is black
// 4. if a node is red, its sons are black
// 5. every path from one node to all its leaves(sentinel) has same number of black nodes

#include "agile_rbtree.h"

static inline void rbtree_left_rotate(rbtree_node_t** root, rbtree_node_t* sentinel, rbtree_node_t* node);
static inline void rbtree_right_rotate(rbtree_node_t** root, rbtree_node_t* sentinel, rbtree_node_t* node);

void rbtree_insert(rbtree_t* tree, rbtree_node_t* node) {
	rbtree_node_t** root;
	rbtree_node_t* temp;
	rbtree_node_t* sentinel;

	root = (rbtree_node_t**)&tree->root;
	sentinel = tree->sentinel;

	if (*root == sentinel) {
		// 1. no parent, root
		node->parent = NULL;
		node->left = sentinel;
		node->right = sentinel;
		rbt_black(node);
		*root = node;
		return;
	}

	tree->insert(*root, node, sentinel);

	// 2. parent is black, don't adjust

	while (node != *root && rbt_is_red(node->parent)) {
		// 3. parent is red, node is red, need adjustment

		if (node->parent == node->parent->parent->left) {
			temp = node->parent->parent->right;
			if (rbt_is_red(temp)) {
				// 3.1 uncle is red, parent and uncle change to black, grandparent change to red, to fullfil rule 5
				rbt_black(node->parent);
				rbt_black(temp);
				rbt_red(node->parent->parent);
				node = node->parent->parent;
			} else {
				if (node == node->parent->right) {
					// unify to 3.2
					node = node->parent;
					rbtree_left_rotate(root, sentinel, node);
				}
				// 3.2 uncle is black, node id red, set grandparent red, set parent black, rotate right
				rbt_black(node->parent);
				rbt_red(node->parent->parent);
				rbtree_right_rotate(root, sentinel, node->parent->parent);
			}
		} else {
			temp = node->parent->parent->left;
			if (rbt_is_red(temp)) {
				// 3.1 uncle is red
				rbt_black(node->parent);
				rbt_black(temp);
				rbt_red(node->parent->parent);
				node = node->parent->parent;
			} else {
				if (node == node->parent->left) {
					// unify to 3.2
					node = node->parent;
					rbtree_right_rotate(root, sentinel, node);
				}
				// 3.2 uncle is black
				rbt_black(node->parent);
				rbt_red(node->parent->parent);
				rbtree_left_rotate(root, sentinel, node->parent->parent);
			}
		}
	}

	rbt_black(*root);
}

void rbtree_delete(rbtree_t* tree, rbtree_node_t* node) {
	uint32_t red;
	rbtree_node_t** root;
	rbtree_node_t* sentinel;
	rbtree_node_t* subst;
	rbtree_node_t* temp;
	rbtree_node_t* w;

	root = (rbtree_node_t**)&tree->root;
	sentinel = tree->sentinel;

	if (node->left == sentinel) {
		temp = node->right;
		subst = node;
	} else if (node->right == sentinel) {
		temp = node->left;
		subst = node;
	} else {
		// both sons are not sentinel
		subst = rbtree_min(node->right, sentinel); // the leftmost nonleaf node of node->right
		if (subst->left != sentinel) {
			temp = subst->left; // it seems program never get here
		} else {
			temp = subst->right;
		}
	}

	if (subst == *root) {
		// at least one of node's son is sentinel and node is root
		*root = temp;
		rbt_black(temp);
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		node->key = 0;
		return;
	}

	red = rbt_is_red(subst);

	// prepare subst to replace node's position
	if (subst == subst->parent->left) {
		subst->parent->left = temp;
	} else {
		subst->parent->right = temp;
	}

	if (subst == node) {
		temp->parent = subst->parent;
	} else {
		if (subst->parent == node) {
			temp->parent = subst; // it seems that it change nothing
		} else {
			temp->parent = subst->parent;
		}

		// subst replace node
		subst->left = node->left;
		subst->right = node->right;
		subst->parent = node->parent;
		rbt_copy_color(subst, node);

		if (node == *root) {
			*root = subst;
		} else {
			if (node == node->parent->left) {
				node->parent->left = subst;
			} else {
				node->parent->right = subst;
			}
		}

		if (subst->left != sentinel) {
			subst->left->parent = subst;
		}

		if (subst->right != sentinel) {
			subst->right->parent = subst;
		}
	}

	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->key = 0;
	
	if (red) return; // subst's original color is red, a red node eleminated do not volate rule 5

	// subst's original color is black, a black node eleminated could affect rule 5
	while (temp != *root && rbt_is_black(temp)) { // loop to adjust the whole tree, if temp is red, quit loop, 
												  // then after the loop program will set it black to add one black node on this tree
		if (temp == temp->parent->left) {
			w = temp->parent->right;

			if (rbt_is_red(w)) {
				// unify
				rbt_black(w);
				rbt_red(temp->parent);
				rbtree_left_rotate(root, sentinel, temp->parent);
				w = temp->parent->right;
			}

			// w is black

			if (rbt_is_black(w->left) && rbt_is_black(w->right)) {
				// both w's sons are black
				// set w red, subtract one black node, continue to check the whole tree
				rbt_red(w);
				temp = temp->parent;
			} else {
				if (rbt_is_black(w->right)) {
					// unify
					rbt_black(w->left);
					rbt_red(w);
					rbtree_right_rotate(root, sentinel, w);
					w = temp->parent->right;
				}

				// w->right is red, w->left is black

				// black node number restore, set temp to root to quit loop
				rbt_copy_color(w, temp->parent);
				rbt_black(temp->parent);
				rbt_black(w->right);
				rbtree_left_rotate(root, sentinel, temp->parent);
				temp = *root;
			}
		} else {
			w = temp->parent->left;

			if (rbt_is_red(w)) {
				rbt_black(w);
				rbt_red(temp->parent);
				rbtree_right_rotate(root, sentinel, temp->parent);
				w = temp->parent->left;
			}

			if (rbt_is_black(w->left) && rbt_is_black(w->right)) {
				rbt_red(w);
				temp = temp->parent;
			} else {
				if (rbt_is_black(w->left)) {
					rbt_black(w->right);
					rbt_red(w);
					rbtree_left_rotate(root, sentinel, w);
					w = temp->parent->left;
				}

				rbt_copy_color(w, temp->parent);
				rbt_black(temp->parent);
				rbt_black(w->left);
				rbtree_right_rotate(root, sentinel, temp->parent);
				temp = *root;
			}
		}
	}

	rbt_black(temp);
}

void rbtree_insert_node(rbtree_node_t* temp, rbtree_node_t* node, rbtree_node_t* sentinel) {
	rbtree_node_t** p;
	for (;;) {
		p = (node->key < temp->key) ? &temp->left : &temp->right;
		if (*p == sentinel) break;
		temp = *p;
	}
	*p = node;
	node->parent = temp;
	node->left = sentinel;
	node->right = sentinel;
	rbt_red(node);
}

rbtree_node_t* rbtree_find_key(rbtree_t* tree, rbtree_key_t key) {
	rbtree_node_t* p = tree->root;
	while (p != tree->sentinel) {
		if (p->key == key) return p;
		p = (p->key < key) ? p->right : p->left;
	}
	return NULL;
}

static inline void rbtree_left_rotate(rbtree_node_t** root, rbtree_node_t* sentinel, rbtree_node_t* node) {
	rbtree_node_t* temp;
	temp = node->right;

	node->right = temp->left;
	if (temp->left != sentinel) {
		temp->left->parent = node;
	}

	temp->parent = node->parent;
	if (node == *root) {
		*root = temp;
	} else if (node == node->parent->left) {
		node->parent->left = temp;
	} else {
		node->parent->right = temp;
	}

	temp->left = node;
	node->parent = temp;
}

static inline void rbtree_right_rotate(rbtree_node_t** root, rbtree_node_t* sentinel, rbtree_node_t* node) {
	rbtree_node_t* temp;
	temp = node->left;

	node->left = temp->right;
	if (temp->right != sentinel) {
		temp->right->parent = node;
	}

	temp->parent = node->parent;
	if (node == *root) {
		*root = temp;
	} else if (node == node->parent->right) {
		node->parent->right = temp;
	} else {
		node->parent->left = temp;
	}

	temp->right = node;
	node->parent = temp;
}

////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

static rbtree_node_t* insert_pair(rbtree_t* rbt, int id, u_char character) {
	rbtree_node_t* node = (rbtree_node_t*)malloc(sizeof (*node));
	if (node == NULL) return NULL;
	node->key = id;
	node->data = character;
	rbtree_insert(rbt, node);
	return node;
}

static void inorder_print(rbtree_t* rbt, rbtree_node_t* node) {
	if (node == rbt->sentinel) return;
	inorder_print(rbt, node->left);
	printf("  %d - %c\n", (int)node->key, node->data);
	inorder_print(rbt, node->right);
}

static void print_tree(rbtree_t* rbt) {
	printf("print tree:\n");
	inorder_print(rbt, rbt->root);
}

void test_agile_rbtree() {
	int i;
	rbtree_node_t* node;
	rbtree_node_t *n1, *n2, *n3, *n4, *n5, *n6;

	rbtree_t rbt;
	rbtree_node_t sentinel;
	
	rbtree_sentinel_init(&sentinel);
	rbtree_init(&rbt, &sentinel, rbtree_insert_node);

	n4 = insert_pair(&rbt, 4, 'd');
	n3 = insert_pair(&rbt, 3, 'c');
	n1 = insert_pair(&rbt, 1, 'a');
	n2 = insert_pair(&rbt, 2, 'b');
	n6 = insert_pair(&rbt, 6, 'f');
	n5 = insert_pair(&rbt, 5, 'e');

	for (i=1; i<=6; ++i) {
		node = rbtree_find_key(&rbt, i);
		if (node) {
			printf("%d : %c\n", i, node->data);
		}
		else {
			printf("failure with key:%d\n", i);
		}
	}

	node = rbtree_find_key(&rbt, 0);
	if (node == NULL) printf("success with key:0\n");
	else printf("failure with key:0\n");

	node = rbtree_find_key(&rbt, 7);
	if (node == NULL) printf("success with key:7\n"); 
	else printf("failure with key:7\n");
	
	print_tree(&rbt);

	rbtree_delete(&rbt, n3); free(n3); n3 = NULL;

	print_tree(&rbt);

	// to delete other nodes...
}
