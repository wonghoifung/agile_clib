#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>

// no extern "C", use g++ to compile all the source files needed
#include "agile_rbtree.h"

// void print_current_time() {
// 	timeval tv;
// 	gettimeofday(&tv, NULL);
// 	printf("current time: %lu.%06lu\n", tv.tv_sec, tv.tv_usec/1000);
// }

void print_elasped_time(timeval& start, timeval& end) {
	timeval tmp;
	tmp.tv_sec = end.tv_sec - start.tv_sec;
    tmp.tv_usec = end.tv_usec - end.tv_usec;
    // normalize
    while (tmp.tv_usec >= 1000000)
    {
      tmp.tv_usec -= 1000000;
      ++tmp.tv_sec;
    }
    while (tmp.tv_usec < 0)
    {
      tmp.tv_usec += 1000000;
      --tmp.tv_sec;
    }
    printf("elasped time: %lu.%06lu\n", tmp.tv_sec, tmp.tv_usec/1000);
}

#define TEST_COUNT 5000000

int main() {

	std::map<int,char> stlmap;

	rbtree_t rbt;
	rbtree_node_t sentinel;
	
	rbtree_sentinel_init(&sentinel);
	rbtree_init(&rbt, &sentinel, rbtree_insert_node);

	// insert
	{
		printf("---------------------> insert\n");
		printf("std map:\n");
		// print_current_time();
		timeval start1;
		gettimeofday(&start1, NULL);
		for (int i=0; i<TEST_COUNT; ++i) {
			stlmap.insert(std::make_pair(i,'a'));
		}
		// print_current_time();
		timeval end1;
		gettimeofday(&end1, NULL);
		print_elasped_time(start1, end1);
		printf("\n");

		printf("agile map:\n");
		// print_current_time();
		timeval start2;
		gettimeofday(&start2, NULL);
		for (int i=0; i<TEST_COUNT; ++i) {
			rbtree_node_t* node = (rbtree_node_t*)malloc(sizeof (*node));
			node->key = i;
			node->data = 'a';
			rbtree_insert(&rbt, node);
		}
		// print_current_time();
		timeval end2;
		gettimeofday(&end2, NULL);
		print_elasped_time(start2, end2);
		printf("\n");
	}

	// search
	{
		printf("---------------------> search\n");
		printf("std map:\n");
		// print_current_time();
		timeval start1;
		gettimeofday(&start1, NULL);
		for (int i=0; i<TEST_COUNT; ++i) {
			std::map<int,char>::iterator it = stlmap.find(i);
			if (it == stlmap.end()) {
				printf("error for std map\n");
				return -1;
			}
		}
		// print_current_time();
		timeval end1;
		gettimeofday(&end1, NULL);
		print_elasped_time(start1, end1);
		printf("\n");

		printf("agile map:\n");
		// print_current_time();
		timeval start2;
		gettimeofday(&start2, NULL);
		for (int i=0; i<TEST_COUNT; ++i) {
			rbtree_node_t* node = rbtree_find_key(&rbt, i);
			if (node == NULL) {
				printf("error for agile map\n");
				return -1;
			}
		}
		// print_current_time();
		timeval end2;
		gettimeofday(&end2, NULL);
		print_elasped_time(start2, end2);
		printf("\n");
	}
	

	// delete
	{
		printf("---------------------> delete\n");
		printf("std map:\n");
		// print_current_time();
		timeval start1;
		gettimeofday(&start1, NULL);
		for (int i=0; i<TEST_COUNT; ++i) {
			stlmap.erase(i);
		}
		// print_current_time();
		timeval end1;
		gettimeofday(&end1, NULL);
		print_elasped_time(start1, end1);
		printf("\n");

		printf("agile map:\n");
		// print_current_time();
		timeval start2;
		gettimeofday(&start2, NULL);
		for (int i=0; i<TEST_COUNT; ++i) {
			rbtree_node_t* node = rbtree_find_key(&rbt, i);
			rbtree_delete(&rbt, node);
			free(node);
		}
		// print_current_time();
		timeval end2;
		gettimeofday(&end2, NULL);
		print_elasped_time(start2, end2);
		printf("\n");
	}
	
	return 0;
}
