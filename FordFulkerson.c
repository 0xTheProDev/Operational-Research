/**
 * Network Flow Problem: Ford Fulkerson algorithm
 * Author: Progyan Bhattacharya <progyanb@acm.org>
 * Repo: Operational-Research [MIT LICENSE]
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN(X, Y) (X) < (Y) ? (X) : (Y)

static int BFS(int n, int rG[n][n], int parent[n], int S, int T) {
    int visited[n], Queue[n], front = -1, rear = -1;
    for (int i = 0; i < n; i++) {
        visited[i] = 1;
    }
    Queue[++rear] = S;
    visited[S] = 0;
    parent[S] = -1;
    while (front < rear) {
        int u = Queue[++front];
        for (int v = 0; v < n; v++) {
            if (visited[v] && rG[u][v] > 0) {
                Queue[++rear] = v;
                visited[v] = 0;
                parent[v] = u;
            }
        }
    }
    return ! visited[T];
}

int MaxFlow(int n, int G[n][n], int S, int T) {
    int maxflow = 0, R[n][n], parent[n];
    for (int i = 0, j = 0; j < n || (j = 0, ++i) < n; j++) {
        if (i == j || G[i][j] < 0) {
            R[i][i] = 0;
            continue;
        }
        R[i][j] = G[i][j];
    }
    while (BFS(n, R, parent, S, T)) {
        int netflow = INT_MAX;
        for (int u = 0, v = T; v != S; v = u) {
            u = parent[v];
            netflow = MIN(netflow, R[u][v]);
        }
        for (int u = 0, v = T; v != S; v = u) {
            u = parent[v];
            R[u][v] -= netflow;
            R[v][u] += netflow;
        }
        maxflow += netflow;
    }
    return maxflow;
}

int main(int argc, char const *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s [n] [S] [T]\n", argv[0]);
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    int S = atoi(argv[2]) - 1;
    int T = atoi(argv[3]) - 1;
    int G[n][n];
    printf("Enter Capacity Matrix of Size %d X %d:\n", n, n);
    for (int i = 0, j = 0; j < n || (j = 0, ++i) < n; j++) {
        scanf("%d", G[i] + j);
    }
    int maxflow = MaxFlow(n, G, S, T);
    printf("Maximum flow in the network is: %d\n", maxflow);
    return EXIT_SUCCESS;
}
