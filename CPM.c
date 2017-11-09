/**
 * Ntework Problem: Critical Path Method
 * Author: Progyan Bhattacharya <progyanb@acm.org>
 * Repo: Operational-Research [MIT LICENSE]
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX(X, Y) (X) > (Y) ? (X) : (Y)
#define MIN(X, Y) (X) < (Y) ? (X) : (Y)

int CPM(int v, int e, double T[e][3], double P[e], int start, int term) {
    double E[v + 1], L[v + 1], X[e][4];
    for (int i = 1; i <= v; i++) {
        E[i] = 0;
    }
    for (int i = 0; i < e; i++) {
        int u = T[i][0], v = T[i][1], d = T[i][2];
        E[v] = MAX(E[u] + d, E[v]);
    }
    for (int i = 1; i <= v; i++) {
        L[i] = INT_MAX;
    }
    L[term] = E[term];
    for (int i = e - 1; i >= 0; i--) {
        int u = T[i][0], v = T[i][1], d = T[i][2];
        L[u] = MIN(L[u], L[v] - d);
    }
    // for (int i = start; i <= term; i++) printf("%d: %d %d\n", i, E[i], L[i]);
    for (int i = 0; i < e; i++) {
        int u = T[i][0], v = T[i][1], d = T[i][2];
        X[i][0] = E[u], X[i][1] = E[u] + d, X[i][2] = L[v] - d, X[i][3] = L[v];
        P[i] = X[i][2] - X[i][0];
    }
    return E[term];
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [v] [e]\n", argv[0]);
        return EXIT_FAILURE;
    }
    int v = atoi(argv[1]), e = atoi(argv[2]);
    double T[e][3], P[e];
    for (int i = 0; i < e; i++) {
        scanf("%lf %lf %lf", T[i], T[i] + 1, T[i] + 2);
    }
    double maxTime = CPM(v, e, T, P, 1, v);
    printf("Maximum Time to Complete: %lf\n", maxTime);
    for (int i = 0; i < e; i++) ! P[i] && printf("%.0lf %.0lf\n", T[i][0], T[i][1]);
    return EXIT_SUCCESS;
}
