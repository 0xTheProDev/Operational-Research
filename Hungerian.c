/**
 * Assignment Problem: Hungerian Method
 * Author: Progyan Bhattacharya <progyanb@acm.org>
 * Repo: Operational-Research [MIT LICENSE]
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int Hungerian(int job, int operator, int Work[job][operator]) {
    int horizontal[job], vertical[operator], Box[job][operator], boxcount;
    if (job != operator) {
        fprintf(stderr, "Error: Unbalanced Assignment Problem Found.\n\
        Number of Job: %d  Number of Operator: %d\n", job, operator);
        exit(EXIT_FAILURE);
    }
    while (1) {
        boxcount = 0;
        for (int i = 0; i < job; i++) {
            horizontal[i] = 0;
        }
        for (int i = 0; i < operator; i++) {
            vertical[i] = 0;
        }
        for (int i = 0; i < job; i++) {
            int min = INT_MAX;
            for (int j = 0; j < operator; j++) {
                if (Work[i][j] < min) {
                    min = Work[i][j];
                }
                Box[i][j] = 0;
            }
            for (int j = 0; min && j < operator; j++) {
                Work[i][j] -= min;
            }
        }
        for (int i = 0; i < operator; i++) {
            int min = INT_MAX;
            for (int j = 0; j < job; j++) {
                if (Work[j][i] < min) {
                    min = Work[j][i];
                }
            }
            for (int j = 0; min && j < job; j++) {
                Work[j][i] -= min;
            }
        }
        for (int i = 0; i < job; i++) {
            int count = 0, k;
            for (int j = 0; j < operator; j++) {
                if (! vertical[j] && ! Work[i][j]) {
                    ++count;
                    k = j;
                }
            }
            if (count == 1) {
                ++boxcount;
                Box[i][k] = 1;
                vertical[k] = 1;
            }
        }
        for (int i = 0; i < operator; i++) {
            int count = 0, k;
            for (int j = 0; ! vertical[i] && j < job; j++) {
                if (! horizontal[j] && ! Work[j][i]) {
                    ++count;
                    k = j;
                }
            }
            if (count == 1) {
                ++boxcount;
                Box[k][i] = 1;
                horizontal[k] = 1;
            }
        }
        if (boxcount == job) {
            break;
        }
        int min = -1;
        for (int i = 0, j = 0; ! horizontal[i] && j < operator || (j = 0, ++i) < job; j++) {
            if (! vertical[j] && (min == -1 || min > Work[i][j])) {
                min = Work[i][j];
            }
        }
        for (int i = 0, j = 0; j < operator || (j = 0, ++i) < job; j++) {
            if (horizontal[i] == vertical[j]) {
                if (horizontal[i]) {
                    Work[i][j] += min;
                } else {
                    Work[i][j] -= min;
                }
            }
        }
    }
    printf("\n   Job        Operator\n");
    for (int i = 0; i < job; i++) {
        int k;
        for (int j = 0; j < operator; j++) {
            if (Box[i][j]) {
                k = j;
                break;
            }
        }
        printf("  %3d          %3d\n", i + 1, k + 1);
    }
}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [row] [col]\n", argv[0]);
        return EXIT_FAILURE;
    }
    int job = atoi(argv[1]), operator = atoi(argv[2]);
    int Work[job][operator];
    for (int i = 0, j = 0; j < operator || (j = 0, ++i) < job; j++) {
        printf("Enter the Time taken to complete Job %d by Operator %d: ", i + 1, j + 1);
        scanf("%d", Work[i] + j);
    }
    int mintime = Hungerian(job, operator, Work);
    return EXIT_SUCCESS;
}
