%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER

%%
expression:
    expression '+' expression   { printf("%d\n", $1 + $3); }
  | expression '-' expression   { printf("%d\n", $1 - $3); }
  | expression '*' expression   { printf("%d\n", $1 * $3); }
  | expression '/' expression   { printf("%d\n", $1 / $3); }
  | NUMBER
  ;
%%
void yyerror(const char *s) {
    printf("Error: %s\n", s);
}

int main() {
    printf("Enter expression:\n");
    yyparse();
    return 0;
}

