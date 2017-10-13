/**
 * Transportation Problem: Least Cost Cell Rule
 * Author: Progyan Bhattacharya <progyanb@acm.org>
 * Repo: Operational-Research [MIT LICENSE]
 */

#include <stdio.h>
#include <stdlib.h>

int LeastCost(int row, int col, int Supply[row], int Demand[col], int Cost[row][col]) {
    int sum = 0, tsup = 0, tdem = 0, Allocate[row][col], minx, miny;
    for (int i = 0; i < row; i++) {
        tsup += Supply[i];
    }
    for (int i = 0; i < col; i++) {
        tdem += Demand[i];
    }
    if (tsup != tdem) {
        fprintf(stderr, "Error: Unbalanced Transportation Problem Found.\n\
        Total Supply: %d  Total Demand: %d\n", tsup, tdem);
        exit(EXIT_FAILURE);
    }
    for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++) {
        Allocate[i][j] = 0;
    }
    while (1) {
        minx = miny = -1;
        for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++) {
            if (Supply[i] && Demand[j] && (minx < 0 || Cost[i][j] < Cost[minx][miny])) {
                minx = i, miny = j;
            }
        }
        if (minx < 0) {
            break;
        }
        if (Supply[minx] > Demand[miny]) {
            Allocate[minx][miny] = Demand[miny];
            Supply[minx] -= Demand[miny];
            Demand[miny] = 0;
        } else {
            Allocate[minx][miny] = Supply[minx];
            Demand[miny] -= Supply[minx];
            Supply[minx] = 0;
        }
    }
    for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++) {
        sum += Allocate[i][j] * Cost[i][j];
    }
    return sum;
}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [row] [col]\n", argv[0]);
        return EXIT_FAILURE;
    }
    int row = atoi(argv[1]), col = atoi(argv[2]);
    int Supply[row], Demand[col], Cost[row][col];
    for (int i = 0; i < row; i++) {
        printf("Enter the Supply by Warehouse %d: ", i + 1);
        scanf("%d", Supply + i);
    }
    for (int i = 0; i < col; i++) {
        printf("Enter the Demand of Consumer %d: ", i + 1);
        scanf("%d", Demand + i);
    }
    for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++) {
        printf("Enter the Cost of Transportation from Warehouse %d to Consumer %d: ", i + 1, j + 1);
        scanf("%d", Cost[i] + j);
    }
    int mincost = LeastCost(row, col, Supply, Demand, Cost);
    printf("Minimal Cost of Transportation: %d\n", mincost);
    return EXIT_SUCCESS;
}
