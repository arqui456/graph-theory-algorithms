//
// Created by arqui on 08/10/2023.
//

#include "algorithms.h"

void dijkstra(graph *g, unsigned int src) {

    if(g == NULL) {
        return;
    }

    int visited[MAX_SIZE];

    priority_queue *queue = new_priority_queue();

    for(int i = 0; i < g->size; i++) {
        g->dist[i] = INT_MAX;
        visited[i] = 0;
        queue->positions[i] = -1;
    }

    g->dist[src] = 0;
    enqueue(queue, src, 0);

    while(!is_empty(queue)) {
        priority_queue_node *min_node = extract_min(queue);
        unsigned int u = min_node->vertex;
        visited[u] = 1;

        node *adj_node = g->nodes[u];
        while(adj_node != NULL) {
            int v = adj_node->vertex;
            int weight = adj_node->weight;

            if(!visited[v] && g->dist[u] != INT_MAX && g->dist[u] + weight < g->dist[v]) {
                g->dist[v] = g->dist[u] + weight;
                if(queue->positions[v] == -1) {
                    enqueue(queue, v, g->dist[v]);
                } else {
                    decrease_priority(queue, v, g->dist[v]);
                }
            }
            adj_node = adj_node->next;
        }
    }
}

disjointed_graph *kruskal(disjointed_graph *g, unsigned int src) {

    if(g == NULL) {
        return NULL;
    }

    int ascendant[g->size];
    int rank[g->size];
    int t = g->size * g->size;
    disjointed_graph *kruskal = new_disj_graph(g->size);

    mergesort(0, t, g->nodes);

    for(int i=0; i < g->size; i++) {
        make_set(ascendant, rank, i);
    }

    for(int i = 0; i < t; i++) {

        if(g->nodes[i]->cost == INT_MAX) {
            break;
        }
        int origin = g->nodes[i]->origin;
        int target = g->nodes[i]->target;
        int cost = g->nodes[i]->cost;
        int ascendant_origin = find_set(ascendant, origin);
        int ascendant_target = find_set(ascendant, target);
        if(ascendant_origin != ascendant_target) {
            kruskal->adj_matrix[origin][target] = cost;
            union_set(ascendant, rank, ascendant_origin, ascendant_target);
        }
    }
    memcpy(kruskal->nodes, g->nodes, g->size);
    free(g);
    return kruskal;
}

void prim(graph *g, unsigned int src, char *output_file, unsigned int print_graph) {

    FILE *file = NULL;

    if(g == NULL) {
        return;
    }

    int size = g->size;
    int parent[size];
    int cost = 0;


    priority_queue *min_heap = new_priority_queue();
    min_heap->capacity = size;

    for(int i = 1;i < size; i++) {
        parent[i] = -1;
        g->dist[i] = INT_MAX;
        min_heap->nodes[i] = new_priority_queue_node(i, g->dist[i]);
        min_heap->positions[i] = i;
    }

    g->dist[0] = 0;
    min_heap->nodes[0] = new_priority_queue_node(0, g->dist[0]);
    min_heap->positions[0] = 0;
    min_heap->size = size;

    while(!is_empty(min_heap)) {
        priority_queue_node *min_heap_node = extract_min(min_heap);
        int u = min_heap_node->vertex;
        node *adj_node = g->nodes[u];
        while(adj_node != NULL) {
            int dest = adj_node->vertex;
            if(min_heap->positions[dest] < min_heap->size && adj_node->weight < g->dist[dest]) {
                g->dist[dest] = adj_node->weight;
                parent[dest] = u;
                decrease_priority(min_heap, dest, g->dist[dest]);
            }
            adj_node = adj_node->next;
        }
    }

    if(output_file != NULL) {
        file = fopen(output_file, "w+");
    }


    if(!print_graph) {
        printf("(%d %d)", parent[1] + 1, 2);
    }

    for(int i = 1; i < g->size; i++) {
        cost += g->dist[i];
        if(!print_graph) {
        printf(" (%d %d)", parent[i] + 1, i + 1);
        }
    }

    if(print_graph) {
        if(output_file != NULL) {
            fprintf(file, "%d", cost);
        } else {
            printf("%d", cost);
        }
    }

    if(file != NULL) {
        fclose(file);
    }
}

void floyd(graph *g, unsigned int src) {


    if (g == NULL) {
        return;
    }

    int adj_matrix[g->size][g->size];


    for (int i = 0; i < g->size; i++) {
        for (int j = 0; j < g->size; j++) {
            adj_matrix[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < g->size; i++) {
        adj_matrix[i][i] = 0;
    }

    for (int i = 0; i < g->size; i++) {
        node *adj_node = g->nodes[i];
        while (adj_node != NULL) {
            adj_matrix[i][adj_node->vertex] = adj_node->weight;
            adj_node = adj_node->next;
        }
    }

    for (int k = 0; k < g->size; k++) {
        for (int i = 0; i < g->size; i++) {
            for (int j = 0; j < g->size; j++) {
                if (adj_matrix[i][k] != INT_MAX && adj_matrix[k][j] != INT_MAX &&
                    adj_matrix[i][k] + adj_matrix[k][j] < adj_matrix[i][j]) {
                    adj_matrix[i][j] = adj_matrix[i][k] + adj_matrix[k][j];
                    if(i == 0) {
                        g->dist[j] = adj_matrix[i][j];
                    }
                }
            }
        }
    }
}
