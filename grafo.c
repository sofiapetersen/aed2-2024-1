#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 20

struct Graph {
    int **pointer;
    int nodes;
    int links;
    int **weight;
}; typedef struct Graph *graph;

graph createGraph(int nodes);
void addWeight(graph g, int src, int dest, int weight);
void printGraphMatrix(graph g);
void dijkstra(graph g, int src, int dest);
int minDistance(int distance[], int visited[], int nodes);
void printShortestDistances(int distance[], int src, int dest);
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

    while(1){
    int src_node, dest_node;
    printf("\nDijkstra Algorithm\nEnter the source node (or -1 to end): ");
    scanf("%d", &src_node);
    if (src_node == -1)
            break;
    printf("Enter the destination node: ");
    scanf("%d", &dest_node);

    dijkstra(g, src_node, dest_node);
    }

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


void dijkstra(graph g, int src, int dest) {
    int distance[MAX_NODES];
    int visited[MAX_NODES] = {0};

    for (int i = 0; i < g->nodes; i++) {
        distance[i] = INT_MAX;
    }
    distance[src] = 0;

    for (int count = 0; count < g->nodes - 1; count++) {
        int u = minDistance(distance, visited, g->nodes);
        visited[u] = 1;

        if (u == dest) // Se o nó de destino foi alcançado, interrompe a busca
            break;

        for (int v = 0; v < g->nodes; v++) {
            if (!visited[v] && g->pointer[u][v] && distance[u] != INT_MAX && distance[u] + g->weight[u][v] < distance[v]) {
                distance[v] = distance[u] + g->weight[u][v];
            }
        }
    }

    printShortestDistances(distance, src, dest);
}


int minDistance(int distance[], int visited[], int nodes) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < nodes; v++) {
        if (!visited[v] && distance[v] <= min) {
            min = distance[v];
            min_index = v;
        }
    }

    return min_index;
}

void printShortestDistances(int distance[], int src, int dest) {
    printf("\nShortest distance from node %d to node %d: %d\n", src, dest, distance[dest]);
}