#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *keywords[] = {
    "main","auto","break","case","char","const","continue","default",
    "do","double","else","enum","extern","float","for","goto",
    "if","int","long","register","return","short","signed","sizeof",
    "static","struct","switch","typedef","unsigned","void","printf","while"
};

int isKeyword(char *s) {
    for (int i = 0; i < 32; i++)
        if (!strcmp(s, keywords[i])) return 1;
    return 0;
}

void printToken(char *tok) {
    if (isKeyword(tok)) printf("%s is keyword\n", tok);
    else if (isdigit(tok[0])) printf("%s is number\n", tok);
    else printf("%s is identifier\n", tok);
}

int main() {
    FILE *fp = fopen("abc.txt", "r");
    if (!fp) { printf("File error\n"); return 0; }

    char ch, buf[100]; int j = 0;
    char *ops = "+-*/%=", *syms = "(),;{}[]";

    while ((ch = fgetc(fp)) != EOF) {
        if (isspace(ch) || strchr(ops, ch) || strchr(syms, ch)) {
            if (j) { buf[j] = '\0'; printToken(buf); j = 0; }
            if (strchr(ops, ch)) printf("%c is operator\n", ch);
            else if (strchr(syms, ch)) printf("%c is symbol\n", ch);
        }
        else if (isalnum(ch) || ch == '_') buf[j++] = ch;
    }
    if (j) { buf[j] = '\0'; printToken(buf); }

    fclose(fp);
    return 0;
}
