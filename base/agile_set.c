#include <string.h>
#include "agile_set.h"

void agile_set_init(agile_set* set, int(*match)(const void*, const void*), void(*destroy)(void*)) {
	agile_list_init(set, destroy);
	set->match = match;
}

int agile_set_insert(agile_set* set, const void* data) {
	if (agile_set_is_member(set, data)) return 1;
	return agile_list_ins_next(set, agile_list_tail(set), data);
}

int agile_set_remove(agile_set* set, void** data) {
	agile_list_element* member, * prev;
	prev = NULL;
	for (member=agile_list_head(set); member!=NULL; member=agile_list_next(member)) {
		if (set->match(*data, agile_list_data(member))) {
			break;
		}
		prev = member;
	}
	if (member == NULL) return -1;
	return agile_list_rem_next(set, prev, data);
}

int agile_set_union(agile_set* setu, const agile_set* set1, const agile_set* set2) {
	agile_list_element* member;
	void* data;
	agile_set_init(setu,set1->match,NULL); 
	for (member=agile_list_head(set1); member!=NULL; member=agile_list_next(member)) {
		data = agile_list_data(member);
		if (agile_list_ins_next(setu, agile_list_tail(setu), data)!=0) {
			agile_set_destroy(setu);
			return -1;
		}
	}
	for (member=agile_list_head(set2); member!=NULL; member=agile_list_next(member)) {
		data = agile_list_data(member);
		if (agile_set_is_member(set1, data)) continue;
		if (agile_list_ins_next(setu, agile_list_tail(setu), data)!=0) {
			agile_set_destroy(setu);
			return -1;
		}
	}
	return 0;
}

int agile_set_intersection(agile_set* seti, const agile_set* set1, const agile_set* set2) {
	agile_list_element* member;
	void* data;
	agile_set_init(seti,set1->match,NULL);
	for (member=agile_list_head(set1); member!=NULL; member=agile_list_next(member)) {
		data = agile_list_data(member);
		if (agile_set_is_member(set2, data)) {
			if (agile_list_ins_next(seti, agile_list_tail(seti), data)!=0) {
				agile_set_destroy(seti);
				return -1;
			}
		}
	}
	return 0;
}

int agile_set_difference(agile_set* setd, const agile_set* set1, const agile_set* set2) {
	agile_list_element* member;
	void* data;
	agile_set_init(setd,set1->match,NULL);
	for (member=agile_list_head(set1); member!=NULL; member=agile_list_next(member)) {
		data = agile_list_data(member);
		if (!agile_set_is_member(set2, data)) {
			if (agile_list_ins_next(setd, agile_list_tail(setd), data)!=0) {
				agile_set_destroy(setd);
				return -1;
			}
		}
	}
	return 0;
}

int agile_set_is_member(const agile_set* set, const void* data) {
	agile_list_element* member;
	for (member=agile_list_head(set); member!=NULL; member=agile_list_next(member)) {
		if (set->match(data, agile_list_data(member))) return 1;
	}
	return 0;
}

// check if set1 is a subset of set2
int agile_set_is_subset(const agile_set* set1, const agile_set* set2) {
	agile_list_element* member;
	if (agile_set_size(set1) > agile_set_size(set2)) return 0;
	for (member=agile_list_head(set1); member!=NULL; member=agile_list_next(member)) {
		if (!agile_set_is_member(set2,agile_list_data(member))) return 0;
	}
	return 1;
}

int agile_set_is_equal(const agile_set* set1, const agile_set* set2) {
	if (agile_set_size(set1) != agile_set_size(set2)) return 0;
	return agile_set_is_subset(set1,set2);
}

//////////////////////////////

#include "test_common.h"

void print_set(agile_set* set, const char* tag) {
	printf("set[%s]: ",tag);
	agile_list_element* member;
	for (member=agile_list_head(set); member!=NULL; member=agile_list_next(member)) {
		printf("%s ", (char*)agile_list_data(member));
	}
	printf("\n");
}

void test_agile_set() {
	agile_set set1,set2;
	agile_set_init(&set1,string_match,free);
	agile_set_init(&set2,string_match,free);

	char* data1_1 = get_data(1);
	char* data2_1 = get_data(2);
	char* data3_1 = get_data(3);
	agile_set_insert(&set1, data1_1);
	agile_set_insert(&set1, data2_1);
	agile_set_insert(&set1, data3_1);
	print_set(&set1,"1");

	char* data1_2 = get_data(1);
	char* data2_2 = get_data(2);
	char* data3_2 = get_data(3);
	agile_set_insert(&set2, data1_2);
	agile_set_insert(&set2, data2_2);
	agile_set_insert(&set2, data3_2);
	print_set(&set2,"2");

	printf("equal: %d\n", agile_set_is_equal(&set1,&set2));
	printf("12subset: %d\n", agile_set_is_subset(&set1,&set2));

	char* data4_1 = get_data(4);
	agile_set_insert(&set1, data4_1);
	printf("12subset: %d\n", agile_set_is_subset(&set1,&set2));
	printf("21subset: %d\n", agile_set_is_subset(&set2,&set1));

	agile_set_destroy(&set1);
	agile_set_destroy(&set2);
}
