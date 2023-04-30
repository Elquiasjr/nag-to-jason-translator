%{
#include <stdio.h>
#include <stdlib.h>
#include "tradutorHeader.h"
%}

%union {
    struct agent *a;
    struct crencas *c;
    struct objetivos *o;
    struct corpo *crp;
    struct content *cnt;
    struct planos *p;
    char *s;
}

%token <s> NAME CRENCAS OBJETIVOS PLANOS
%token <s> OU NAO E

%type <a> agent agentlist
%type <s> eventoGatilho contexto expLogica
%type <c> lCrencas nCrencas
%type <o> lObjetivos nObjetivo
%type <p> lPlanos nomePlano
%type <cnt> tuplaPlano
%type <crp> corpo formulasCorpo


%start agentlist


%%

agentlist: /*vazio*/ { $$ = NULL;}
    | agent agentlist { $$ = insertAgent($1, $2);
    }
    ;

agent: NAME CRENCAS lCrencas OBJETIVOS lObjetivos PLANOS lPlanos {
    $$ = newAgent($1, $3, $5, $7);
    writeAgent($$);
}
    ;

lCrencas: '{' nCrencas '}' {$$ = $2;}
    ;

nCrencas:  { $$ = NULL;}
    | NAME ';' nCrencas {$$ = insertCrenca(newCrenca($1), $3);}
    ;

lObjetivos: '{' nObjetivo '}' {$$ = $2;}
    ;

nObjetivo: { $$ = NULL;}
    | NAME ';' nObjetivo {$$ = insertObjetivo(newObjetivo($1), $3);}
    ;

lPlanos: '{' nomePlano '}' {$$ = $2;}
    ;

nomePlano: { $$ = NULL;}
    | NAME tuplaPlano ';' nomePlano {$$ = insertPlano(newPlano($1, $2), $4);}
    ;

tuplaPlano: '(' eventoGatilho ';' contexto ';' corpo ')' {$$ = newContent($2, $4, $6);}
    ;

eventoGatilho: NAME {$$ = $1;}
    ;

contexto: {$$ = NULL;}
    |NAME {$$ = $1;}
    | expLogica {$$ = $1;}
    ;

expLogica: NAME E NAME { $$ = threecat($1, " & ", $3);}
    | NAME OU NAME { $$ = threecat($1, " | ", $3); }
    | NAO NAME { $$ = stringcat("not ", $2); }
    ;

corpo:  '{' formulasCorpo '}' {$$ = $2;}
    ;

formulasCorpo: { $$ = NULL ;}
    | NAME ';' formulasCorpo {$$ = insertCorpo( newCorpo($1), $3);}
    ;

%%