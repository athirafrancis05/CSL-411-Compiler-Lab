%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER

%%
input:
    expression '\n'   { printf("= %d\n", $1); }
  ;

expression:
    expression '+' expression   { $$ = $1 + $3; }
  | expression '-' expression   { $$ = $1 - $3; }
  | expression '*' expression   { $$ = $1 * $3; }
  | expression '/' expression   { $$ = $1 / $3; }
  | '(' expression ')'          { $$ = $2; }
  | NUMBER                      { $$ = $1; }
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
