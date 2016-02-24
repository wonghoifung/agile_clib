#include <float.h>
#include <stdlib.h>
#include "agile_graph_alg.h"

int agile_mst(agile_graph* graph, const agile_mst_vertex* start, agile_list* span, int(*match)(const void*,const void*)) {
	agile_adj_list* adjlist;
	agile_mst_vertex* mst_vertex;
	agile_mst_vertex* adj_vertex;
	agile_list_element* element;
	agile_list_element* member;
	double minimum;
	int found, i;
	found = 0;
	// init
	for (element=agile_list_head(&agile_graph_adjlists(graph)); element!=NULL; element=agile_list_next(element)) {
		mst_vertex = ((agile_adj_list*)agile_list_data(element))->vertex;
		if (match(mst_vertex, start)) {
			mst_vertex->color = white;
			mst_vertex->key = 0;
			mst_vertex->parent = NULL;
			found = 1;
		} else {
			mst_vertex->color = white;
			mst_vertex->key = DBL_MAX;
			mst_vertex->parent = NULL;
		}
	}
	if (!found) return -1;
	i = 0;
	// prim's algorithm
	while (i < agile_graph_vcount(graph)) {
		minimum = DBL_MAX;
		for (element=agile_list_head(&agile_graph_adjlists(graph)); element!=NULL; element=agile_list_next(element)) {
			mst_vertex = ((agile_adj_list*)agile_list_data(element))->vertex;
			if (mst_vertex->color == white && mst_vertex->key < minimum) {
				minimum = mst_vertex->key;
				adjlist = agile_list_data(element);
			}
		}
		((agile_mst_vertex*)adjlist->vertex)->color = black;
		for (member=agile_list_head(&adjlist->adjacent); member!=NULL; member=agile_list_next(member)) {
			adj_vertex = agile_list_data(member);
			for (element=agile_list_head(&agile_graph_adjlists(graph)); element!=NULL; element=agile_list_next(element)) {
				mst_vertex = ((agile_adj_list*)agile_list_data(element))->vertex;
				if (match(mst_vertex, adj_vertex)) {
					if (mst_vertex->color == white && adj_vertex->weight < mst_vertex->key) {
						mst_vertex->key = adj_vertex->weight;
						mst_vertex->parent = adjlist->vertex;
					}
					break;
				}
			}
		}
		i += 1;
	}
	// result
	agile_list_init(span, NULL);
	for (element=agile_list_head(&agile_graph_adjlists(graph)); element!=NULL; element=agile_list_next(element)) {
		mst_vertex = ((agile_adj_list*)agile_list_data(element))->vertex;
		if (mst_vertex->color == black) {
			if (agile_list_ins_next(span, agile_list_tail(span), mst_vertex) != 0) {
				agile_list_destroy(span);
				return -1;
			}
		}
	}
	return 0;
}

int agile_shortest(agile_graph* graph, const agile_path_vertex* start, agile_list* paths, int(*match)(const void*,const void*)) {

}

int agile_tsp(agile_graph* graph, const agile_tsp_vertex* start, agile_list* tour, int(*match)(const void*,const void*)) {

}

//////////////////////////////

void test_agile_graph_alg() {

}
