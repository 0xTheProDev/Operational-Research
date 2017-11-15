/**
 * LP Problem: Find Dual of a Primal Problem
 * Author: Progyan Bhattacharya <progyanb@acm.org>
 * Repo: Operational-Research [MIT LICENSE]
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void Dual(int m, int n, int A[m][n], int B[m], int C[n]) {
    printf("Dual of the given problem:\nMinimize Z = ");
    for (int i = 0; i < m || ! putchar('\n'); i++) {
        printf(" %c (%d)y%d", i ? '+' : '\0', B[i], i + 1);
    }
    printf("Subject to Constraints:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf(" %c (%d)y%d", j ? '+' : '\0', A[j][i], j + 1);
        }
        printf(" >= %d\n", C[i]);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [m] [n]\n", argv[0]);
        return EXIT_FAILURE;
    }
    int m = atoi(argv[1]), n = atoi(argv[2]);
    int A[m][n], B[m], C[n];
    printf("Objective function for Minimization\n");
    for (int i = 0; i < n; i++) {
        printf("Enter the co-efficient of x%d: ", i + 1);
        scanf("%d", C + i);
    }
    printf("Constraint inequalities\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Enter the co-efficients of %d for inequality %d: ", j + 1, i + 1);
            scanf("%d", A[i] + j);
        }
        printf("Enter the constraint of inequality %d: ", i + 1);
        scanf("%d", B + i);
    }
    Dual(m, n, A, B, C);
    return EXIT_SUCCESS;
}
