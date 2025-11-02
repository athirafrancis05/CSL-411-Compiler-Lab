#include <stdio.h>
#include <string.h>

typedef struct { int from; char sym; int to; } Transition;

int contains(int s, int arr[10], int n) {
    for (int i = 0; i < n; i++) if (arr[i] == s) return 1;
    return 0;
}

void eclosure(int s, int arr[10], int n, int *cnt, Transition t[]) {
    if (!contains(s, arr, *cnt)) arr[(*cnt)++] = s;
    for (int i = 0; i < n; i++)
        if (t[i].from == s && t[i].sym == 'e')
            eclosure(t[i].to, arr, n, cnt, t);
}

void main() {
    int nstates, ntrans, nsyms;
    Transition t[10];
    char syms[10];
    int closure[10][10], ccount[10], table[10][10][10], tcount[10][10] = {0};

    printf("Enter number of states: "); scanf("%d", &nstates);
    printf("Enter number of symbols: "); scanf("%d", &nsyms);
    printf("Enter symbols: "); for (int i = 0; i < nsyms; i++) scanf(" %c", &syms[i]);
    printf("\nEnter number of transitions: "); scanf("%d", &ntrans);

    FILE *f = fopen("test.txt", "r");
    for (int i = 0; i < ntrans; i++) fscanf(f, "%d %c %d", &t[i].from, &t[i].sym, &t[i].to);

    for (int i = 0; i < nstates; i++) {
        int c = 0; eclosure(i, closure[i], ntrans, &c, t); ccount[i] = c;
    }

    for (int i = 0; i < nstates; i++)
        for (int k = 0; k < nsyms; k++) {
            int final[10] = {0}, fcnt = 0;
            for (int j = 0; j < ccount[i]; j++)
                for (int l = 0; l < ntrans; l++)
                    if (t[l].from == closure[i][j] && t[l].sym == syms[k])
                        eclosure(t[l].to, final, ntrans, &fcnt, t);
            for (int n = 0; n < fcnt; n++) table[i][k][n] = final[n];
            tcount[i][k] = fcnt;
        }

    printf("Final States:\n");
    for (int i = 0; i < nstates; i++)
        for (int j = 0; j < nsyms; j++) {
            printf("δ(q%d, %c) = { ", i, syms[j]);
            for (int k = 0; k < tcount[i][j]; k++)
                if (table[i][j][k] != 0 || k == 0) printf("%d ", table[i][j][k]);
            printf("}\n");
        }
}

