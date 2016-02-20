#include <string.h>
#include "agile_graph.h"

void agile_graph_init(agile_graph* graph, int(*match)(const void*,const void*), void(*destroy)(void*)) {

}

void agile_graph_destroy(agile_graph* graph) {

}

int agile_graph_ins_vertex(agile_graph* graph, const void* data) {

}

int agile_graph_ins_edge(agile_graph* graph, const void* data1, const void* data2) {

}

int agile_graph_rem_vertex(agile_graph* graph, void** data) {

}

int agile_graph_rem_edge(agile_graph* graph, void** data1, void** data2) {

}

int agile_graph_adjlist(const agile_graph* graph, const void* data, agile_adj_list** adjlist) {

}

int agile_graph_is_adjacent(const agile_graph* graph, const void* data1, const void* data2) {

}

//////////////////////////////

#include "test_common.h"

void test_agile_graph() {

}
