#include <string.h>
#include "agile_graph.h"

void agile_graph_init(agile_graph* graph, int(*match)(const void*,const void*), void(*destroy)(void*)) {
	graph->vcount = 0;
	graph->ecount = 0;
	graph->match = match;
	graph->destroy = destroy;
	agile_list_init(&graph->adjlists, NULL);
}

void agile_graph_destroy(agile_graph* graph) {
	agile_adj_list* adjlist;
	while (agile_list_size(&graph->adjlists) > 0) {
		if (agile_list_rem_next(&graph->adjlists, NULL, (void**)&adjlist) == 0) {
			agile_set_destroy(&adjlist->adjacent);
			if (graph->destroy != NULL) graph->destroy(adjlist->vertex);
			free(adjlist);
		}
	}
	agile_list_destroy(&graph->adjlists);
	memset(graph, 0, sizeof(agile_graph));
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
