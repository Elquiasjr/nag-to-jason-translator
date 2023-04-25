/* Exemplo de Multiplos Arquivo no Flex (contagem de palavras) */
%option noyywrap nodefault yylineno
/* desabilita o analisador léxico */
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

"NAO" {printf("NAO\n"); return NAO; }
"OU" {printf("OU\n"); return OU; }
"E" {printf("E\n"); return E;}
"crencas:" {printf("Crencas\n"); return CRENCAS; }
"objetivos:" {printf("Objetivos\n"); return OBJETIVOS; }
"planos:" { printf("Planos\n"); return PLANOS; }
[ \t]
[a-zA-Z][a-zA-Z0-9]* { yylval.s = strdup(yytext); printf("Nome: %s\n", yytext); return NAME; }
[\n]
[\\\n]


. { yyerror("Caracter nao reconhecido %c\n", *yytext);}

%%
