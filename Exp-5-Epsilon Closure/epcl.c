#include <stdio.h>
#include <stdlib.h>
#define MAX 10

int n;                          
int eclosure[MAX][MAX];         
int transition[MAX][MAX];       
int visited[MAX];               

void dfs(int state, int start) {
    if (visited[state]) return;
    visited[state] = 1;
    eclosure[start][state] = 1;

    for (int i = 0; i < n; i++) {
        if (transition[state][i] == 1) {
            dfs(i, start);
        }
    }
}
int main() {
    int i, j;   
    printf("Enter number of states in NFA: ");
    scanf("%d", &n);
    printf("Enter ε-transition matrix (%d x %d):\n", n, n);
    printf("(1 if epsilon transition exists, else 0)\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &transition[i][j]);
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            eclosure[i][j] = 0;
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) visited[j] = 0;
        dfs(i, i);
    }
    printf("\nε-Closure of each state:\n");
    for (i = 0; i < n; i++) {
        printf("ε-closure(q%d) = { ", i);
        for (j = 0; j < n; j++) {
            if (eclosure[i][j] == 1) {
                printf("q%d ", j);
            }
        }
        printf("}\n");
    }
    return 0;
}
