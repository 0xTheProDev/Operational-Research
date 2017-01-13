#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void dijkstraSP(int n, int G[n][n], int S) {
    int D[n], P[n], ps;
    for (int i = 0; i < n; i++) {
        D[i] = INT_MAX;
        P[i] = 1;
    }
    D[S] = 0, ps = S;
    for (int k = 0; k < n - 1; k++) {
        P[ps] = 0;
        int cur = D[ps], ms = -1;
        for (int i = 0; i < n; i++) {
            if (P[i] && G[ps][i]) {
                int d = cur + G[ps][i];
                if (D[i] > d) {
                    D[i] = d;
                }
                if (ms < 0 || D[ms] > D[i]) {
                    ms = i;
                }
            }
        }
        ps = ms;
    }
    for (int i = 0; i < n; i++) {
        i ^ S && printf("Shortest path between %d and %d is %d\n", S + 1,
        i + 1, D[i]);
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [n] [S]\n", argv[0]);
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    int S = atoi(argv[2]) - 1;
    int G[n][n];
    for (int i = 0, j = 0; j < n || (j = 0, ++i) < n; j++) {
        if (i ^ j) {
            printf("Enter weight of G[%d][%d]: ", i + 1, j + 1);
            scanf("%d", &G[i][j]);
        } else {
            G[i][j] = 0;
        }
    }
    dijkstraSP(n, G, S);
    return EXIT_SUCCESS;
}
