//
// Created by arqui on 26/09/2023.
//

#include "graph.h"

node *new_node(int vertex, int weight) {
    node *new_node = (node*) malloc(sizeof(node));
    new_node->vertex = vertex;
    new_node->weight = weight;
    new_node->next = NULL;
    return new_node;
}

priority_queue_node *new_priority_queue_node(unsigned int vertex, int priority) {
    priority_queue_node *new_node = (priority_queue_node*) malloc(sizeof(priority_queue_node));
    new_node->vertex = vertex;
    new_node->priority = priority;
    return new_node;
}

graph *new_graph(int size) {
    graph *g = (graph*) malloc(sizeof(graph));
    g->size = size;
    for(int i=0; i < size; i++) {
        g->nodes[i] = NULL;
    }
    return g;
}

void add_node(graph *g, int src, int dest, int weight) {
    node *n = new_node(dest, weight);
    n->next = g->nodes[src];
    g->nodes[src] = n;
    n = new_node(src, weight);
    n->next = g->nodes[dest];
    g->nodes[dest] = n;
}

priority_queue *new_priority_queue() {
    priority_queue *queue = (priority_queue*) malloc(sizeof(priority_queue));
    queue->size = 0;
    return queue;
}

void swap(priority_queue_node **a, priority_queue_node **b) {
    priority_queue_node *temp = *a;
    *a = *b;
    *b = temp;
}


void min_heapify(priority_queue *queue, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if(left < queue->size && queue->nodes[left]->priority < queue->nodes[smallest]->priority) {
        smallest = left;
    }

    if(right < queue->size && queue->nodes[right]->priority < queue->nodes[smallest]->priority) {
        smallest = right;
    }

    if(smallest != index) {
        queue->positions[queue->nodes[smallest]->vertex] = index;
        queue->positions[queue->nodes[index]->vertex] = smallest;
        swap(&queue->nodes[smallest], &queue->nodes[index]);
        min_heapify(queue, smallest);
    }
}

int is_empty(priority_queue *queue) {
    return (queue->size == 0);
}

priority_queue_node *extract_min(priority_queue *queue) {

    if(is_empty(queue)) {
        return NULL;
    }

    priority_queue_node *root = queue->nodes[0];
    priority_queue_node *last_node = queue->nodes[queue->size - 1];
    queue->nodes[0] = last_node;
    queue->positions[root->vertex] = queue->size -1;
    queue->positions[last_node->vertex] = 0;
    queue->size -= 1;
    min_heapify(queue, 0);

    return root;
}

void decrease_priority(priority_queue *queue, unsigned int vertex, int priority) {

    int index = queue->positions[vertex];
    queue->nodes[index]->priority = priority;

    while(index > 0 && queue->nodes[index]->priority < queue->nodes[(index - 1) / 2]->priority) {
        queue->positions[queue->nodes[index]->vertex] = (index - 1) / 2;
        queue->positions[queue->nodes[(index - 1) / 2]->vertex] = index;
        swap(&queue->nodes[index], &queue->nodes[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void enqueue(priority_queue *queue, unsigned int vertex, int priority) {

    int index = 0;
    priority_queue_node *new_node = new_priority_queue_node(vertex, priority);
    queue->nodes[queue->size] = new_node;
    queue->positions[vertex] = queue->size;
    queue->size += 1;

    index = queue->size - 1;
    while(index > 0 && queue->nodes[index]->priority < queue->nodes[(index - 1) / 2]->priority) {
        queue->positions[queue->nodes[index]->vertex] = (index - 1) / 2;
        queue->positions[queue->nodes[(index - 1) / 2]->vertex] = index;
        swap(&queue->nodes[index], &queue->nodes[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void make_set(int *ascendant, int *rank, int x) {

    ascendant[x] = x;
    rank[x] = 0;

}

int find_set(int *ascendant, int target) {

    while(ascendant[target] != target) {
        target = ascendant[target];
    }

    return ascendant[target];

}

void union_set(int *ascendant, int *rank, int x, int y) {

    if(rank[x] > rank[y]) {
        ascendant[y] = x;
    } else {
        ascendant[x] = y;
        if(rank[x] == rank[y]) {
            rank[y]++;
        }
    }
}

disjointed_graph *new_disj_graph(int size) {

    disjointed_graph *g = (disjointed_graph *) malloc(sizeof(disjointed_graph));
    g->size = size;
    for(int i = 0; i < size * size; i++) {
        g->nodes[i] = new_disj_node();
    }

    return g;
}

disjointed_graph_node *new_disj_node() {

    disjointed_graph_node *disj_graph_node = (disjointed_graph_node *) malloc(sizeof(disjointed_graph_node));
    disj_graph_node->cost = INT_MAX;
    disj_graph_node->origin = -1;
    disj_graph_node->target = -1;

    return disj_graph_node;
}

void add_disj_node(disjointed_graph *g, int origin, int target, int cost) {

    int index = origin * g->size + target;
    g->adj_matrix[origin][target] = cost;
    g->nodes[index]->origin = origin;
    g->nodes[index]->target = target;
    g->nodes[index]->cost = cost;
}

static void merge(int p, int q, int r, disjointed_graph_node **node) {

    int i, j, k;
    disjointed_graph_node **aux_node = (disjointed_graph_node **) malloc((r - p) * sizeof(disjointed_graph_node *));
    i = p;
    j = q;
    k = 0;

    while(i < q && j < r) {
        if(node[i]->cost <= node[j]->cost) {
            aux_node[k++] = node[i++];
        } else {
            aux_node[k++] = node[j++];
        }
    }

    while(i < q) {
        aux_node[k++] = node[i++];
    }

    while(j < r) {
        aux_node[k++] = node[j++];
    }

    for(i = p; i < r; ++i) {
        node[i] = aux_node[i - p];
    }

    free(aux_node);
}

void mergesort(int p, int r, disjointed_graph_node **nodes) {

    if(p < r - 1) {
        int q = (p + r) / 2;
        mergesort(p, q, nodes);
        mergesort(q, r, nodes);
        merge(p, q, r, nodes);
    }

}



