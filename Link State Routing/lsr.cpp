#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_NODES 100

int dijkstra(int n, int adj[][MAX_NODES], int src, int dest, int *path);

int main() {
    int n, src, dest;
    int adj[MAX_NODES][MAX_NODES];
    int path[MAX_NODES];
    int i, j, cost;
    printf("Enter the number of nodes in the network: ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix representing the network:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }
    printf("Enter the source node: ");
    scanf("%d", &src);
    printf("Enter the destination node: ");
    scanf("%d", &dest);
    cost = dijkstra(n, adj, src, dest, path);
    if (cost == INT_MAX) {
        printf("No path found from node %d to node %d\n", src, dest);
    } 
    else {
        printf("Shortest path from node %d to node %d:\n", src, dest);
        for (i = 0; i <= path[0]; i++) {
            printf("%d ", path[i]);
        }
        printf("\nTotal cost of path: %d\n", cost);
    }
    return 0;
}

int dijkstra(int n, int adj[MAX_NODES][MAX_NODES], int src, int dest, int *path) {
    int dist[MAX_NODES];
    int visited[MAX_NODES];
    int i, j, min, u;
    for (i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        path[i] = -1;
    }
    dist[src] = 0;
    for (i = 0; i < n - 1; i++) {
        min = INT_MAX;
        for (j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }
        visited[u] = 1;
        for (j = 0; j < n; j++) {
            if (!visited[j] && adj[u][j] && dist[u] != INT_MAX && dist[u] + adj[u][j] < dist[j]) {
                dist[j] = dist[u] + adj[u][j];
                path[j] = u;
            }
        }
    }
    if (dist[dest] == INT_MAX) {
        return INT_MAX;
    }
}
