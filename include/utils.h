//
// Created by arqui on 01/10/2023.
//

#ifndef GRAPH_TEORY_ALGORITHMS_UTILS_H
#define GRAPH_TEORY_ALGORITHMS_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graph.h"
#include "algorithms.h"


typedef enum Algorithm {Prim = 0, Kruskal, Floyd, Dijkstra, NoAlgorithm} Algorithm;

void help(Algorithm alg);
void print_graph(graph *g, unsigned int src, char *output_file);
void print_disjointed_graph(disjointed_graph *g, unsigned int print_graph, char *output_file);
int handle_argvs(int argc, char **argv, Algorithm alg);

#endif //GRAPH_TEORY_ALGORITHMS_UTILS_H
