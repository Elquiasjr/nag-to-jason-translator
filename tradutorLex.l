%option noyywrap nodefault yylineno
%{
#include "tradutorHeader.h"
#include "tradutorBison.tab.h"
%}

%%

";" |
"{" |
"}" |
"(" |
")" { return yytext[0];}

"NAO" { return NAO; }
"OU" { return OU; }
"E" { return E;}
"crencas:" { return CRENCAS; }
"objetivos:" { return OBJETIVOS; }
"planos:" { return PLANOS; }
[ \t]
[a-zA-Z][a-zA-Z0-9]* { yylval.s = strdup(yytext); return NAME; }
[\n]
[\\\n]


. { yyerror("Caracter nao reconhecido %c\n", *yytext);}

%%
