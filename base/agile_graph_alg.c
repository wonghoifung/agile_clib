#include <float.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

static void relax(agile_path_vertex* u, agile_path_vertex* v, double weight) {
	if (v->d > u->d + weight) {
		v->d = u->d + weight;
		v->parent = u;
	}
}

int agile_shortest(agile_graph* graph, const agile_path_vertex* start, agile_list* paths, int(*match)(const void*,const void*)) {
	agile_adj_list* adjlist;
	agile_path_vertex* pth_vertex;
	agile_path_vertex* adj_vertex;
	agile_list_element* element;
	agile_list_element* member;
	double minimum;
	int found, i;
	found = 0;
	// init
	for (element=agile_list_head(&agile_graph_adjlists(graph)); element!=NULL; element=agile_list_next(element)) {
		pth_vertex = ((agile_adj_list*)agile_list_data(element))->vertex;
		if (match(pth_vertex, start)) {
			pth_vertex->color = white;
			pth_vertex->d = 0;
			pth_vertex->parent = NULL;
			found = 1;
		} else {
			pth_vertex->color = white;
			pth_vertex->d = DBL_MAX;
			pth_vertex->parent = NULL;
		}
	}
	if (!found) return -1;
	// dijkstra's algorithm
	i = 0;
	while (i < agile_graph_vcount(graph)) {
		minimum = DBL_MAX;
		for (element=agile_list_head(&agile_graph_adjlists(graph)); element!=NULL; element=agile_list_next(element)) {
			pth_vertex = ((agile_adj_list*)agile_list_data(element))->vertex;
			if (pth_vertex->color == white && pth_vertex->d < minimum) {
				minimum = pth_vertex->d;
				adjlist = agile_list_data(element);
			}
		}
		((agile_path_vertex*)adjlist->vertex)->color = black;
		for (member=agile_list_head(&adjlist->adjacent); member!=NULL; member=agile_list_next(member)) {
			adj_vertex = agile_list_data(member);
			for (element=agile_list_head(&agile_graph_adjlists(graph)); element!=NULL; element=agile_list_next(element)) {
				pth_vertex = ((agile_adj_list*)agile_list_data(element))->vertex;
				if (match(pth_vertex, adj_vertex)) {
					relax(adjlist->vertex, pth_vertex, adj_vertex->weight);
				}
			}
		}
		i += 1;
	}
	// result
	agile_list_init(paths, NULL);
	for (element=agile_list_head(&agile_graph_adjlists(graph)); element!=NULL; element=agile_list_next(element)) {
		pth_vertex = ((agile_adj_list*)agile_list_data(element))->vertex;
		if (pth_vertex->color == black) {
			if (agile_list_ins_next(paths, agile_list_tail(paths), pth_vertex) != 0) {
				agile_list_destroy(paths);
				return -1;
			}
		}
	}
	return 0;
}

int agile_tsp(agile_graph* graph, const agile_tsp_vertex* start, agile_list* tour, int(*match)(const void*,const void*)) {

}

//////////////////////////////

static int mst_vertex_match(const void* data1, const void* data2) {
	if (strcmp((char*)(((agile_mst_vertex*)data1)->data), (char*)(((agile_mst_vertex*)data2)->data))==0) return 1;
	return 0;
}

static int shortest_vertex_match(const void* data1, const void* data2) {
	if (strcmp((char*)(((agile_path_vertex*)data1)->data), (char*)(((agile_path_vertex*)data2)->data))==0) return 1;
	return 0;
}

static void mst_print_list(agile_list* list) {
	agile_list_element* elm = agile_list_head(list);
	while (elm != NULL) {
		agile_mst_vertex* mst_vertex = (agile_mst_vertex*)agile_list_data(elm);
		if (mst_vertex->parent) {
			printf("%s parent:%s\n", (char*)(mst_vertex->data), (char*)(mst_vertex->parent->data));
		} else {
			printf("%s parent:null\n", (char*)(mst_vertex->data));
		}
		
		elm = agile_list_next(elm);
	}
}

static void shortest_print_list(agile_list* list) {
	agile_list_element* elm = agile_list_head(list);
	while (elm != NULL) {
		agile_path_vertex* pth_vertex = (agile_path_vertex*)agile_list_data(elm);
		if (pth_vertex->parent) {
			printf("%s parent:%s\n", (char*)(pth_vertex->data), (char*)(pth_vertex->parent->data));
		} else {
			printf("%s parent:null\n", (char*)(pth_vertex->data));
		}
		
		elm = agile_list_next(elm);
	}
}

static void test_agile_mst() {
	agile_graph graph;
	agile_graph_init(&graph, mst_vertex_match, NULL);
	
	char* a = "a";
	char* b = "b";
	char* c = "c";
	char* d = "d";
	char* e = "e";
	char* f = "f";
	agile_mst_vertex amv; amv.data = (void*)a; amv.parent = NULL;
	agile_mst_vertex bmv; bmv.data = (void*)b; bmv.parent = NULL;
	agile_mst_vertex cmv; cmv.data = (void*)c; cmv.parent = NULL;
	agile_mst_vertex dmv; dmv.data = (void*)d; dmv.parent = NULL;
	agile_mst_vertex emv; emv.data = (void*)e; emv.parent = NULL;
	agile_mst_vertex fmv; fmv.data = (void*)f; fmv.parent = NULL;

	agile_graph_ins_vertex(&graph, (void*)&amv);
	agile_graph_ins_vertex(&graph, (void*)&bmv);
	agile_graph_ins_vertex(&graph, (void*)&cmv);
	agile_graph_ins_vertex(&graph, (void*)&dmv);
	agile_graph_ins_vertex(&graph, (void*)&emv);
	agile_graph_ins_vertex(&graph, (void*)&fmv);

	agile_mst_vertex abmv = bmv; abmv.weight = 7;
	agile_mst_vertex acmv = cmv; acmv.weight = 4;
	agile_graph_ins_edge(&graph, (void*)&amv, (void*)&abmv);
	agile_graph_ins_edge(&graph, (void*)&amv, (void*)&acmv);

	agile_mst_vertex bamv = amv; bamv.weight = 7;
	agile_mst_vertex bcmv = cmv; bcmv.weight = 6;
	agile_mst_vertex bdmv = dmv; bdmv.weight = 2;
	agile_mst_vertex bfmv = fmv; bfmv.weight = 4;
	agile_graph_ins_edge(&graph, (void*)&bmv, (void*)&bamv);
	agile_graph_ins_edge(&graph, (void*)&bmv, (void*)&bcmv);
	agile_graph_ins_edge(&graph, (void*)&bmv, (void*)&bdmv);
	agile_graph_ins_edge(&graph, (void*)&bmv, (void*)&bfmv);

	agile_mst_vertex camv = amv; camv.weight = 4;
	agile_mst_vertex cbmv = bmv; cbmv.weight = 6;
	agile_mst_vertex cemv = emv; cemv.weight = 9;
	agile_mst_vertex cfmv = fmv; cfmv.weight = 8;
	agile_graph_ins_edge(&graph, (void*)&cmv, (void*)&camv);
	agile_graph_ins_edge(&graph, (void*)&cmv, (void*)&cbmv);
	agile_graph_ins_edge(&graph, (void*)&cmv, (void*)&cemv);
	agile_graph_ins_edge(&graph, (void*)&cmv, (void*)&cfmv);

	agile_mst_vertex dbmv = bmv; dbmv.weight = 2;
	agile_mst_vertex dfmv = fmv; dfmv.weight = 7;
	agile_graph_ins_edge(&graph, (void*)&dmv, (void*)&dbmv);
	agile_graph_ins_edge(&graph, (void*)&dmv, (void*)&dfmv);

	agile_mst_vertex ecmv = cmv; ecmv.weight = 9;
	agile_mst_vertex efmv = fmv; efmv.weight = 1;
	agile_graph_ins_edge(&graph, (void*)&emv, (void*)&ecmv);
	agile_graph_ins_edge(&graph, (void*)&emv, (void*)&efmv);

	agile_mst_vertex fbmv = bmv; fbmv.weight = 4;
	agile_mst_vertex fcmv = cmv; fcmv.weight = 8;
	agile_mst_vertex fdmv = dmv; fdmv.weight = 7;
	agile_mst_vertex femv = emv; femv.weight = 1;
	agile_graph_ins_edge(&graph, (void*)&fmv, (void*)&fbmv);
	agile_graph_ins_edge(&graph, (void*)&fmv, (void*)&fcmv);
	agile_graph_ins_edge(&graph, (void*)&fmv, (void*)&fdmv);
	agile_graph_ins_edge(&graph, (void*)&fmv, (void*)&femv);

	agile_list span;
	int res = agile_mst(&graph, &amv, &span, mst_vertex_match);
	printf("res: %d\n", res);
	mst_print_list(&span);

	agile_graph_destroy(&graph);
}

void test_agile_shortest() {
agile_graph graph;
	agile_graph_init(&graph, shortest_vertex_match, NULL);
	
	char* a = "a";
	char* b = "b";
	char* c = "c";
	char* d = "d";
	char* e = "e";
	char* f = "f";
	agile_path_vertex amv; amv.data = (void*)a; amv.parent = NULL;
	agile_path_vertex bmv; bmv.data = (void*)b; bmv.parent = NULL;
	agile_path_vertex cmv; cmv.data = (void*)c; cmv.parent = NULL;
	agile_path_vertex dmv; dmv.data = (void*)d; dmv.parent = NULL;
	agile_path_vertex emv; emv.data = (void*)e; emv.parent = NULL;
	agile_path_vertex fmv; fmv.data = (void*)f; fmv.parent = NULL;

	agile_graph_ins_vertex(&graph, (void*)&amv);
	agile_graph_ins_vertex(&graph, (void*)&bmv);
	agile_graph_ins_vertex(&graph, (void*)&cmv);
	agile_graph_ins_vertex(&graph, (void*)&dmv);
	agile_graph_ins_vertex(&graph, (void*)&emv);
	agile_graph_ins_vertex(&graph, (void*)&fmv);

	agile_path_vertex abmv = bmv; abmv.weight = 8;
	agile_path_vertex acmv = cmv; acmv.weight = 4;
	agile_graph_ins_edge(&graph, (void*)&amv, (void*)&abmv);
	agile_graph_ins_edge(&graph, (void*)&amv, (void*)&acmv);

	agile_path_vertex bcmv = cmv; bcmv.weight = 6;
	agile_path_vertex bdmv = dmv; bdmv.weight = 2;
	agile_path_vertex bfmv = fmv; bfmv.weight = 4;
	agile_graph_ins_edge(&graph, (void*)&bmv, (void*)&bcmv);
	agile_graph_ins_edge(&graph, (void*)&bmv, (void*)&bdmv);
	agile_graph_ins_edge(&graph, (void*)&bmv, (void*)&bfmv);

	agile_path_vertex cemv = emv; cemv.weight = 4;
	agile_path_vertex cfmv = fmv; cfmv.weight = 1;
	agile_graph_ins_edge(&graph, (void*)&cmv, (void*)&cemv);
	agile_graph_ins_edge(&graph, (void*)&cmv, (void*)&cfmv);

	agile_path_vertex efmv = fmv; efmv.weight = 5;
	agile_graph_ins_edge(&graph, (void*)&emv, (void*)&efmv);

	agile_path_vertex fbmv = bmv; fbmv.weight = 2;
	agile_path_vertex fdmv = dmv; fdmv.weight = 7;
	agile_path_vertex femv = emv; femv.weight = 4;
	agile_graph_ins_edge(&graph, (void*)&fmv, (void*)&fbmv);
	agile_graph_ins_edge(&graph, (void*)&fmv, (void*)&fdmv);
	agile_graph_ins_edge(&graph, (void*)&fmv, (void*)&femv);

	agile_list paths;
	int res = agile_shortest(&graph, &amv, &paths, shortest_vertex_match);
	printf("res: %d\n", res);
	shortest_print_list(&paths);

	agile_graph_destroy(&graph);
}

void test_agile_graph_alg() {
	test_agile_mst();
	printf("\n");
	test_agile_shortest();
}
