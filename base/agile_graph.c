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
	agile_list_element* element;
	agile_adj_list* adjlist;
	int retval;
	for (element = agile_list_head(&graph->adjlists); element!=NULL; element=agile_list_next(element)) {
		if (graph->match(data, ((agile_adj_list*)agile_list_data(element))->vertex)) return 1;
	}
	if ((adjlist = (agile_adj_list*)malloc(sizeof(agile_adj_list))) == NULL) return -1;
	adjlist->vertex = (void*)data;
	agile_set_init(&adjlist->adjacent, graph->match, NULL);
	if ((retval = agile_list_ins_next(&graph->adjlists, agile_list_tail(&graph->adjlists), adjlist)) != 0) {
		return retval;
	}
	graph->vcount += 1;
	return 0;
}

// insert data2 into data1's adjacent
int agile_graph_ins_edge(agile_graph* graph, const void* data1, const void* data2) {
	agile_list_element* element;
	int retval;
	for (element=agile_list_head(&graph->adjlists); element!=NULL; element=agile_list_next(element)) {
		if (graph->match(data2, ((agile_adj_list*)agile_list_data(element))->vertex)) break;
	}
	if (element==NULL) return -1;
	for (element=agile_list_head(&graph->adjlists); element!=NULL; element=agile_list_next(element)) {
		if (graph->match(data1, ((agile_adj_list*)agile_list_data(element))->vertex)) break;
	}
	if (element==NULL) return -1;
	if ((retval = agile_set_insert(&((agile_adj_list*)agile_list_data(element))->adjacent, data2)) != 0) {
		return retval;
	}
	graph->ecount += 1;
	return 0;
}

int agile_graph_rem_vertex(agile_graph* graph, void** data) {
	agile_list_element* element;
	agile_list_element* temp;
	agile_list_element* prev;
	agile_adj_list* adjlist;
	int found;
	prev = NULL;
	found = 0;
	for (element=agile_list_head(&graph->adjlists); element!=NULL; element=agile_list_next(element)) {
		// should remove edge before vertex
		if (agile_set_is_member(&((agile_adj_list*)agile_list_data(element))->adjacent, *data)) return -1;
		if (graph->match(*data, ((agile_adj_list*)agile_list_data(element))->vertex)) {
			temp = element;
			found = 1;
		}
		if (!found) prev = element;
	}
	if (!found) return -1;
	if (agile_set_size(&((agile_adj_list*)agile_list_data(element))->adjacent) > 0) return -1;
	if (agile_list_rem_next(&graph->adjlists, prev, (void**)&adjlist) != 0) return -1;
	*data = adjlist->vertex;
	free(adjlist);
	graph->vcount -= 1;
	return 0;
}

int agile_graph_rem_edge(agile_graph* graph, void** data1, void** data2) {
	agile_list_element* element;
	for (element=agile_list_head(&graph->adjlists); element!=NULL; element=agile_list_next(element)) {
		if (graph->match(data1, ((agile_adj_list*)agile_list_data(element))->vertex)) break;
	}
	if (element==NULL) return -1;
	if (agile_set_remove(&((agile_adj_list*)agile_list_data(element))->adjacent, data2) != 0) return -1;
	graph->ecount -= 1;
	return 0;
}

int agile_graph_adjlist(const agile_graph* graph, const void* data, agile_adj_list** adjlist) {
	agile_list_element* element;
	//agile_list_element* prev;
	//prev = NULL;
	for (element=agile_list_head(&graph->adjlists); element!=NULL; element=agile_list_next(element)) {
		if (graph->match(data, ((agile_adj_list*)agile_list_data(element))->vertex)) break;
		//prev = element;
	}
	if (element==NULL) return -1;
	*adjlist = agile_list_data(element);
	return 0;
}

int agile_graph_is_adjacent(const agile_graph* graph, const void* data1, const void* data2) {
	agile_list_element* element;
	agile_list_element* prev;
	prev = NULL;
	for (element=agile_list_head(&graph->adjlists); element!=NULL; element=agile_list_next(element)) {
		if (graph->match(data1, ((agile_adj_list*)agile_list_data(element))->vertex)) break;
		prev = element;
	}
	if (element==NULL) return 0;
	return agile_set_is_member(&((agile_adj_list*)agile_list_data(element))->adjacent, data2);
}

//////////////////////////////

#include "test_common.h"

void test_agile_graph() {

}
