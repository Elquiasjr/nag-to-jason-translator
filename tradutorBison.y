%{
#include <stdio.h>
#include <stdlib.h>
#include "tradutorHeader.h"
%}

%union {
    struct agent *a;
    char *s;
}

%token <s> NAME CRENCAS OBJETIVOS PLANOS
%token <s> OU NAO E

%type <a> agent
%type <s> lCrencas nCrencas lObjetivos nObjetivo lPlanos nomePlano tuplaPlano eventoGatilho contexto expLogica corpo formulasCorpo


%start agent


%%

agent: NAME CRENCAS lCrencas OBJETIVOS lObjetivos PLANOS lPlanos {
    $$ = newAgent($1, $3, $5, $7);
}
    ;

lCrencas: '{' nCrencas '}' {$$ = $2;}
    ;

nCrencas:  { $$ = NULL;}
    | NAME ';' nCrencas {$$ = stringcat( $1, $3);}
    ;

lObjetivos: { $$ = NULL;}
    | '{' nObjetivo '}' {$$ = $2;}
    ;

nObjetivo: { $$ = NULL;}
    | NAME ';' nObjetivo {$$ = stringcat( $1, $3);}
    ;

lPlanos: '{' nomePlano '}' {$$ = $2;}
    ;

nomePlano: { $$ = NULL;}
    | NAME tuplaPlano ';' nomePlano {$$ = threecat($1, $2, $4);}
    ;

tuplaPlano: '(' eventoGatilho ';' contexto ';' corpo ')' {$$ = threecat($2, $4, $6);}
    ;

eventoGatilho: NAME {$$ = $1;}
    ;

contexto: {$$ = NULL;}
    |NAME {$$ = $1;}
    | expLogica {$$ = $1;}
    ;

expLogica: NAME E NAME { $$ = threecat($1, $2, $3);}
    | NAME OU NAME { $$ = threecat($1, $2, $3); }
    | NAO NAME { $$ = stringcat($1, $2); }
    ;

corpo:  '{' formulasCorpo '}' {$$ = $2;}
    ;

formulasCorpo: { $$ = NULL ;}
    | NAME ';' formulasCorpo {$$ = stringcat( $1, $3);}
    ;

%%