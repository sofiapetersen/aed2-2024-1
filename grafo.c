#include <stdio.h>
#include <stdlib.h>

struct Graph {
    int **pointer;
    int nodes;
    int links;
    int **weight;
}; typedef struct Graph *graph;

graph createGraph(int nodes);
void addWeight(graph g, int src, int dest, int weight);
void printGraphMatrix(graph g);
void freeGraph(graph g);

int main () {

    int nodes = 0;

    while (nodes > 20 || nodes < 2) {
    printf("Number of nodes: ");
    scanf("%d", &nodes);
    }

     graph g = createGraph(nodes);

    int src, dest, weight;
    while (1) {
        printf("\nCONECTIONS\nType source vertice, destination vertice, weight or -1 to end: ");
        scanf("%d", &src);

        if (src == -1)
            break;

        scanf("%d %d", &dest, &weight);

        if (src < 0 || src >= nodes || dest < 0 || dest >= nodes || weight < 0) {
            printf("Invalid conection!\n");
            continue;
        }
        addWeight(g, src, dest, weight);
    }

    printGraphMatrix(g);
    freeGraph(g);

    return 0;

}

graph createGraph(int nodes) {
    graph g = (graph)malloc(sizeof(struct Graph));
    g->nodes = nodes;
    g->links = 0;
    g->pointer = (int **)malloc(nodes * sizeof(int *));
    g->weight = (int **)malloc(nodes * sizeof(int *));

//peso zero em todas
    for (int i = 0; i < nodes; i++) {
        g->pointer[i] = (int *)calloc(nodes, sizeof(int));
        g->weight[i] = (int *)calloc(nodes, sizeof(int));
    }

    return g;
}

void addWeight(graph g, int src, int dest, int weight) {
    if (src >= 0 && src < g->nodes && dest >= 0 && dest < g->nodes) {
        g->pointer[src][dest] = 1;
        g->weight[src][dest] = weight;
        g->links++;
    }
}

void printGraphMatrix(graph g) {
    printf("Matrix:\n");

    printf("   ");
    for (int i = 0; i < g->nodes; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    for (int i = 0; i < g->nodes; i++) {
        printf("%2d ", i);
        for (int j = 0; j < g->nodes; j++) {
            if (g->pointer[i][j] == 1) {
                printf("%2d ", g->weight[i][j]);
            } else {
                printf(" 0 ");
            }
        }
        printf("\n");
    }
}

void freeGraph(graph g) {
    if (g) {
        if (g->pointer) {
            for (int i = 0; i < g->nodes; i++) {
                free(g->pointer[i]);
            }
            free(g->pointer);
        }

        if (g->weight) {
            for (int i = 0; i < g->nodes; i++) {
                free(g->weight[i]);
            }
            free(g->weight);
        }

        free(g);
    }
}

