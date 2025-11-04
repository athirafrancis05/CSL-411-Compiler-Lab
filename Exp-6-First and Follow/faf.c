#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char production[MAX][10];
char first[MAX][10];
char follow[MAX][10];
int n;

void findFirst(char*, char);
void findFollow(char*, char);
int isNonTerminal(char);

int main() {
    int i;
    char ch;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter the productions (use # for epsilon):\n");
    for (i = 0; i < n; i++) {
        scanf("%s", production[i]);
    }

    for (i = 0; i < n; i++) {
        strcpy(first[i], "");
        findFirst(first[i], production[i][0]);
    }

    for (i = 0; i < n; i++) {
        strcpy(follow[i], "");
        findFollow(follow[i], production[i][0]);
    }

    printf("\nFIRST and FOLLOW sets:\n");
    for (i = 0; i < n; i++) {
        printf("FIRST(%c) = { %s }\n", production[i][0], first[i]);
        printf("FOLLOW(%c) = { %s }\n\n", production[i][0], follow[i]);
    }

    return 0;
}

int isNonTerminal(char c) {
    return (c >= 'A' && c <= 'Z');
}
void findFirst(char* result, char c) {
    int i, j;
    char subResult[10];
    if (!isNonTerminal(c)) {
        if (strchr(result, c) == NULL)
            strncat(result, &c, 1);
        return;
    }
    for (i = 0; i < n; i++) {
        if (production[i][0] == c) {
            if (production[i][2] == '#') {
                if (strchr(result, '#') == NULL)
                    strcat(result, "#");
            } else {
                j = 2;
                while (production[i][j] != '\0') {
                    findFirst(subResult, production[i][j]);
                    strcat(result, subResult);
                    if (strchr(subResult, '#') == NULL)
                        break;
                    j++;
                }
            }
        }
    }
}
void findFollow(char* result, char c) {
    int i, j, k;
    char subResult[10];

    if (production[0][0] == c) 
        strcat(result, "$");

    for (i = 0; i < n; i++) {
        for (j = 2; production[i][j] != '\0'; j++) {
            if (production[i][j] == c) {
                if (production[i][j + 1] != '\0') {
                    findFirst(subResult, production[i][j + 1]);
                    strcat(result, subResult);
                } else if (production[i][0] != c) {
                    findFollow(subResult, production[i][0]);
                    strcat(result, subResult);
                }
            }
        }
    }
}


