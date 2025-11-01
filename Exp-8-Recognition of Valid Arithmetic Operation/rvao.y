%{
#include <stdio.h>
#include <stdlib.h>
// Forward declarations
int yylex(void);
int yyerror(const char *s);
%}
%token NUMBER ID
%left '+' '-' '*' '/'
%%
exp : exp '+' exp
| exp '-' exp
| exp '*' exp
| exp '/' exp
| '(' exp ')'
| NUMBER
| ID
;
%%
int main(int argc, char *argv[]) {
printf("Enter the expression: ");
yyparse();
printf("Valid Expression!\n");
return 0;
}
int yyerror(const char *s) {
printf("Invalid Expression! %s\n", s);
exit(1);
}
int yywrap(void) {
return 1;
}
