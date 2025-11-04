%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+          { yylval = atoi(yytext); return NUMBER; }
[+\-*/() \t]    { return yytext[0]; }
\n              { return '\n'; }
.               { /* ignore anything else */ }
%%

int yywrap() {
    return 1;
}
