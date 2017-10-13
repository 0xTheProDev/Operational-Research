/**
 * Transportation Problem: North West Corner Cell Rule
 * Author: Progyan Bhattacharya <progyanb@acm.org>
 * Repo: Operational-Research [MIT LICENSE]
 */

#include <stdio.h>
#include <stdlib.h>

int NorthWest(int row, int col, int Supply[row], int Demand[col], int Cost[row][col]) {
    int sum = 0, tsup = 0, tdem = 0, Allocate[row][col];
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
    for (int i = 0, j = 0; i < row && j < col;) {
        if (Supply[i] > Demand[j]) {
            Allocate[i][j] = Demand[j];
            Supply[i] -= Demand[j];
            Demand[j] = 0;
            j++;
        } else {
            Allocate[i][j] = Supply[i];
            Demand[j] -= Supply[i];
            Supply[i] = 0;
            i++;
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
    int mincost = NorthWest(row, col, Supply, Demand, Cost);
    printf("Minimal Cost of Transportation: %d\n", mincost);
    return EXIT_SUCCESS;
}
