#ifndef agile_graph_header
#define agile_graph_header

#include <stdlib.h>
#include "agile_list.h"
#include "agile_set.h"

typedef struct agile_adj_list_ {
	void* vertex;
	agile_set adjacent;
} agile_adj_list;

typedef struct agile_graph_ {
	int vcount;
	int ecount;
	int (*match)(const void* key1, const void* key2);
	void (*destroy)(void* data);
	agile_list adjlists;
} agile_graph;

typedef enum agile_vertex_color_ {
	white,
	gray,
	black
} agile_vertex_color;

void agile_graph_init(agile_graph* graph, int(*match)(const void*,const void*), void(*destroy)(void*));
void agile_graph_destroy(agile_graph* graph);
int agile_graph_ins_vertex(agile_graph* graph, const void* data);
int agile_graph_ins_edge(agile_graph* graph, const void* data1, const void* data2);
int agile_graph_rem_vertex(agile_graph* graph, void** data);
int agile_graph_rem_edge(agile_graph* graph, void** data1, void** data2);
int agile_graph_adjlist(const agile_graph* graph, const void* data, agile_adj_list** adjlist);
int agile_graph_is_adjacent(const agile_graph* graph, const void* data1, const void* data2);

#define agile_graph_adjlists(graph) ((graph)->adjlists)
#define agile_graph_vcount(graph) ((graph)->vcount)
#define agile_graph_ecount(graph) ((graph)->ecount)

void test_agile_graph();

#endif
