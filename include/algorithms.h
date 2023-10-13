//
// Created by arqui on 08/10/2023.
//

#ifndef GRAPH_THEORY_ALGORITHMS_ALGORITHMS_H
#define GRAPH_THEORY_ALGORITHMS_ALGORITHMS_H

#include "graph.h"

void dijkstra(graph *g, unsigned int src);
void floyd(graph *g, unsigned int src);
disjointed_graph *kruskal(disjointed_graph *g, unsigned int src);
void prim(graph *g, unsigned int src, char *output_file, unsigned int print_graph);

#endif //GRAPH_THEORY_ALGORITHMS_ALGORITHMS_H
