//
// Created by arqui on 26/09/2023.
//

#ifndef GRAPH_THEORY_ALGORITHMS_GRAPH_H
#define GRAPH_THEORY_ALGORITHMS_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_SIZE 50000

typedef struct node node;
typedef struct priority_queue_node priority_queue_node;
typedef struct priority_queue priority_queue;
typedef struct graph graph;
typedef struct disjointed_graph disjointed_graph;
typedef struct disjointed_graph_node disjointed_graph_node;
typedef struct min_spanning_tree min_spanning_tree;

struct min_spanning_tree {
    int *parent;
    int cost;
};

struct node {
    int vertex;
    int weight;
    node *next;
};

struct priority_queue_node {
    int vertex;
    int priority;
};

struct priority_queue {
    priority_queue_node *nodes[MAX_SIZE];
    int size;
    int capacity;
    int positions[MAX_SIZE];
};

struct graph {
    node *nodes[MAX_SIZE];
    int dist[MAX_SIZE];
    int size;
};

struct disjointed_graph {
    int adj_matrix[MAX_SIZE][MAX_SIZE];
    disjointed_graph_node *nodes[MAX_SIZE];
    int size;
};

struct disjointed_graph_node {
    int origin;
    int target;
    int cost;
};


node *new_node(int vertex, int weight);
priority_queue_node *new_priority_queue_node(unsigned int vertex, int priority);
graph *new_graph(int size);
void add_node(graph *g, int src, int dest, int weight);
priority_queue *new_priority_queue();
void swap(priority_queue_node **a, priority_queue_node **b);
void min_heapify(priority_queue *queue, int index);
int is_empty(priority_queue *queue);
priority_queue_node *extract_min(priority_queue *queue);
void decrease_priority(priority_queue *queue, unsigned int vertex, int priority);
void enqueue(priority_queue *queue, unsigned int vertex, int priority);
void make_set(int *ascendant, int *rank, int x);
int find_set(int *ascendant, int x);
void union_set(int *ascendant, int *rank, int x, int y);
void mergesort(int p, int r, disjointed_graph_node **nodes);
disjointed_graph *new_disj_graph(int size);
disjointed_graph_node *new_disj_node();
void add_disj_node(disjointed_graph *g, int origin, int target, int cost);



#endif //GRAPH_THEORY_ALGORITHMS_GRAPH_H
