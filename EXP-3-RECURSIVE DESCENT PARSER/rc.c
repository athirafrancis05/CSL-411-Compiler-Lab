#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
char input[100];
int i = 0;
void E();
void Eprime();
void T();
void Tprime();
void F();
void error() {
    printf("Not Accepted\n");
    exit(0);
}
void match(char c) {
    if (input[i] == c)
        i++;
    else
        error();
}
void F() {
    if (input[i] == 'i')
        match('i');
    else
        error();
}
void T() {
    F();
    Tprime();
}
void Tprime() {
    if (input[i] == '*') {
        match('*');
        F();
        Tprime();
    }
}
void E() {
    T();
    Eprime();
}
void Eprime() {
    if (input[i] == '+') {
        match('+');
        T();
        Eprime();
    }
}
int main() {
    printf("Enter the input expression: ");
    fgets(input, sizeof(input), stdin);
    int len = strlen(input);
    if (input[len - 1] == '\n') input[len - 1] = '\0';   
    strcat(input, "$"); // ensure input ends with $
    E();
    if (input[i] == '$')
        printf("Accepted\n");
    else
        printf("Not Accepted\n");

    return 0;
}

