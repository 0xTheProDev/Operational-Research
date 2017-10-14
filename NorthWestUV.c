/**
 * Transportation Problem: MOdified DIstribution Method
 * Phase I: North West Corner Cell Rule for BFS
 * Phase II: U-V Method for Optimal Solution
 * Author: Progyan Bhattacharya <progyanb@acm.org>
 * Repo: Operational-Research [MIT LICENSE]
 */

#include <stdio.h>
#include <stdlib.h>

void NorthWest(int row, int col, int Supply[row], int Demand[col], int Cost[row][col], int Allocate[row][col]) {
    int tsup = 0, tdem = 0;
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
}

void UVOptimize(int row, int col, int Cost[row][col], int Allocate[row][col]) {
    int count = 0, U[row], V[col], Penalty[row][col], maxx = -1, maxy = -1;
    for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++) {
        if (Allocate[i][j]) {
            count++;
        }
    }
    if (count != row + col - 1) {
        fprintf(stderr, "Error: Invalid Problem for Optimal Solution\n\
        Number of Allocated Cell: %d\n", count);
        exit(EXIT_FAILURE);
    }
    while(1) {
        U[0] = 0;
        for (int i = 1; i < row; i++) {
            U[i] = -1;
        }
        for (int i = 0; i < col; i++) {
            V[i] = -1;
        }
        for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++) {
            if (Allocate[i][j]) {
                if (U[i] != -1) {
                    V[j] = Cost[i][j] - U[i];
                } else {
                    U[i] = Cost[i][j] - V[j];
                }
                Penalty[i][j] = 0;
            }
        }
        for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++) {
            if (! Allocate[i][j]) {
                Penalty[i][j] = U[i] + V[j] - C[i][j];
            }
            if (max == -1 || Penalty[i][j] > Penalty[maxx][maxy]) {
                maxx = i, maxy = j;
            }
        }
        if (maxx == -1 || Penalty[maxx][maxy] < 0) {
            printf("Optimal Solution has already been reached.\n");
            return;
        }

        // for (int i = 0; i < row; i++) {
        //     printf("U[%d]=%d ", i + 1, U[i]);
        // }
        // for (int i = 0; i < col; i++) {
        //     printf("V[%d]=%d ", i + 1, V[i]);
        // }
        // puts("");
    }
}

int getCost(int row, int col, int Cost[row][col], int Allocate[row][col]) {
    int sum = 0;
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
    if (row <= 0 || col <= 0) {
        fprintf(stderr, "Error: Invalid size of rows and/or column found.\n");
        return EXIT_FAILURE;
    }
    int Supply[row], Demand[col], Cost[row][col], Allocate[row][col];
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
    NorthWest(row, col, Supply, Demand, Cost, Allocate);
    UVOptimize(row, col, Cost, Allocate);
    int mincost = getCost(row, col, Cost, Allocate);
    printf("Minimal Cost of Transportation: %d\n", mincost);
    return EXIT_SUCCESS;
}
