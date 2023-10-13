//
// Created by arqui on 01/10/2023.
//

#include "utils.h"

static char INPUT_FILE[MAX_SIZE];
static char OUTPUT_FILE[MAX_SIZE];
static unsigned int INITIAL_VERTEX = 0;
static unsigned char PRINT_GRAPH = 1;
static unsigned char OUTPUT_TO_FILE = 0;

void print_graph(graph *g, unsigned int src, char *output_file) {

    FILE *file = NULL;

    if(output_file != NULL) {
        file = fopen(output_file, "w+");
        fprintf(file, "1:0 ");
    } else {
        printf("1:0 ");
    }

    for(int i = 0; i < g->size; i++) {
        if(i != src) {
            if(output_file != NULL) {
                fprintf(file, "%d:", i + 1);
                if(g->dist[i] == INT_MAX) {
                    fprintf(file, "-1 ");
                } else {
                    fprintf(file, "%d ", g->dist[i]);
                }
            } else {
                printf("%d:", i + 1);
                if (g->dist[i] == INT_MAX) {
                    printf("-1 ");
                } else {
                    printf("%d ", g->dist[i]);
                }
            }
        }
    }

    if(output_file != NULL) {
        fclose(file);
    }
}

void print_disjointed_graph(disjointed_graph *g, unsigned int print_graph, char *output_file) {

    FILE *file = NULL;
    int first = 1;
    int total_cost = 0;

    if(output_file != NULL) {
        file = fopen(output_file, "w+");
    }

    for(int i = 0; i < g->size; i++) {
        for(int j = 0; j < g->size; j++) {
            if(g->adj_matrix[i][j] == 0) {
                continue;
            }
            if(print_graph) {
                if(file != NULL) {
                    if(first) {
                        fprintf(file, "(%d %d)", (i + 1), (j + 1));
                        first = 0;
                    } else {
                        fprintf(file, " (%d %d)", (i + 1), (j + 1));
                    }
                } else {
                    if(first) {
                        printf("(%d %d)", (i + 1), (j + 1));
                        first = 0;
                    } else {
                        printf(" (%d %d)", (i + 1), (j + 1));
                    }
                }
            }
            total_cost += g->adj_matrix[i][j];
        }
    }

    if(!print_graph) {
        if(output_file != NULL) {
            fprintf(file, "%d", total_cost);
        } else {
            printf("%d", total_cost);
        }
    }

    if(file != NULL) {
        fclose(file);
    }

}

int handle_argvs(int argc, char **argv, Algorithm alg) {

    FILE *file = NULL;
    int i, v_num, a_num, v1, v2, c;
    char line[MAX_SIZE];
    graph *g = NULL;
    disjointed_graph *dsj = NULL;

    for(i = 1;i < argc; i++) {
        if(!strcmp(argv[i], "-f")) {
            strcpy(INPUT_FILE, argv[i + 1]);
            file = fopen(INPUT_FILE, "r");
            if(file == NULL) {
                printf("File %s not found.\n", INPUT_FILE);
                return -1;
            }
            fgets(line, sizeof(line), file);
            sscanf(line, "%d %d", &v_num, &a_num);
            if(alg != Kruskal) {
                g = new_graph(v_num);
            } else {
                dsj = new_disj_graph(v_num);
            }
            while(fgets(line, sizeof(line), file)) {
                sscanf(line, "%d %d %d", &v1, &v2, &c);
                if(alg != Kruskal) {
                    add_node(g, v1 - 1, v2 - 1, c);
                } else {
                    add_disj_node(dsj, v1 - 1, v2 - 1, c);
                }
            }
            fclose(file);
        } else if(!strcmp(argv[i], "-i")) {
            sscanf(argv[i + 1], "%u", &INITIAL_VERTEX);
        } else if(!strcmp(argv[i], "-o")) {
            strcpy(OUTPUT_FILE, argv[i + 1]);
            OUTPUT_TO_FILE = 1;
        } else if(!strcmp(argv[i], "-h")) {
            help(alg);
        } else if(!strcmp(argv[i], "-s")) {
            PRINT_GRAPH = 0;
        }
    }

    if(!g && !dsj) {
        return 0;
    }

    switch (alg) {
        case Prim:
            if(OUTPUT_TO_FILE) {
                prim(g, INITIAL_VERTEX, OUTPUT_FILE, PRINT_GRAPH);
            } else {
                prim(g, INITIAL_VERTEX, NULL, PRINT_GRAPH);
            }
            OUTPUT_TO_FILE = 0;
            PRINT_GRAPH = 0;
            break;
        case Kruskal:
            dsj = kruskal(dsj, INITIAL_VERTEX);
            PRINT_GRAPH = !PRINT_GRAPH;
            if(OUTPUT_TO_FILE) {
                print_disjointed_graph(dsj, PRINT_GRAPH, OUTPUT_FILE);
            } else {
                print_disjointed_graph(dsj, PRINT_GRAPH, NULL);
            }
            OUTPUT_TO_FILE = 0;
            PRINT_GRAPH = 0;
            free(dsj);
            break;
        case Floyd:
            floyd(g, INITIAL_VERTEX);
            break;
        case Dijkstra:
            dijkstra(g, INITIAL_VERTEX);
            break;
        case NoAlgorithm:
            printf("No algorithm selected \n");
            break;
    }

    if(OUTPUT_TO_FILE) {
        print_graph(g, INITIAL_VERTEX, OUTPUT_FILE);
    }

    if(PRINT_GRAPH) {
        print_graph(g,INITIAL_VERTEX, NULL);
    }

    if(g != NULL) {
        free(g);
    }
    return 0;
}

void help(Algorithm alg) {

    switch (alg) {
        case Prim:
            printf("Usage: prim.bin [OPTIONS]... \n");
            break;
        case Kruskal:
            printf("Usage: kruskal.bin [OPTIONS]... \n");
            break;
        case Floyd:
            printf("Usage: floyd.bin [OPTIONS]... \n");
            break;
        case Dijkstra:
            printf("Usage: dijkstra.bin [OPTIONS]... \n");
            break;
        case NoAlgorithm:
            printf("Usage: algorithm.bin [OPTIONS]... \n");
    }

    printf(" -f <file>   indica o 'arquivo' que contem o grafo de entrada \n");
    printf(" -o <file>   redireciona a saida para o 'arquivo' \n");
    printf(" -s          mostra a solucao \n");
    printf(" -i          vertice inicial \n");
}