#ifndef agile_graph_alg_header
#define agile_graph_alg_header

#include "agile_graph.h"
#include "agile_list.h"

// vertex for minimum spanning tree
typedef struct agile_mst_vertex_ {
	void* data;
	double weight;
	agile_vertex_color color;
	double key;
	struct agile_mst_vertex_* parent;
} agile_mst_vertex;

// vertex for shortest path problems
typedef struct agile_path_vertex_ {
	void* data;
	double weight;
	agile_vertex_color color;
	double d;
	struct agile_path_vertex_* parent;
} agile_path_vertex;

// vertex for traveling salesman problems
typedef struct agile_tsp_vertex_ {
	void* data;
	double x;
	double y;
	agile_vertex_color color;
} agile_tsp_vertex;

// weighted graph without direction
int agile_mst(agile_graph* graph, const agile_mst_vertex* start, agile_list* span, int(*match)(const void*,const void*));
// weighted graph with direction
int agile_shortest(agile_graph* graph, const agile_path_vertex* start, agile_list* paths, int(*match)(const void*,const void*));
// weighted graph without direction
int agile_tsp(agile_graph* graph, const agile_tsp_vertex* start, agile_list* tour, int(*match)(const void*,const void*));

void test_agile_graph_alg();

#endif
