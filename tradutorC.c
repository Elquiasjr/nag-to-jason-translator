#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "tradutorHeader.h"

void writeAgent(struct agent *agentlist);

char *curfilename; 

struct agent* newAgent(char *nome, char *crencas, char *objetivos, char *planos){
    struct agent *newA = (struct agent*) malloc(sizeof(struct agent));
    
    if(newA == NULL){
        printf("Erro: falha na alocação de memória. \n");
        exit(1);
    }

    newA->nome = nome;
    newA->crencas = crencas;
    newA->objetivos = objetivos;
    newA->planos = planos;
    newA->prox = NULL;
    
    writeAgent(newA);

    return newA;
}

char * newString(char *ytext){
    char *s = (char*)malloc(strlen(ytext) + 1);
    strcpy(s, ytext);
    return s;
}

char * stringcat(char *a, char *b){
    if(b == NULL){
        return a;
    }
    if(a == NULL){
        return b;
    }
    char *s = (char*)malloc(strlen(a) + strlen(b) + 1);
    strcat(s, a);
    strcat(s, b);
    return s;
}

char * threecat(char *a, char *b, char *c){
    if(a == NULL){
        return stringcat(b, c);
    }
    if(b == NULL){
        return stringcat(a, c);
    }
    if(c == NULL){
        return stringcat(a, b);
    }

    char *s = (char*)malloc(strlen(a) + strlen(b) + strlen(c) + 1);
    strcat(s, a);
    strcat(s, b);
    strcat(s, c);
    return s;
}

char * fourcat(char *a, char *b, char *c, char *d){
    if(a == NULL){
        return threecat(b, c, d);
    }
    if(b == NULL){
        return threecat(a, c, d);
    }
    if(c == NULL){
        return threecat(a, b, d);
    }
    if(d == NULL){
        return threecat(a, b, c);
    }

    char *s = (char*)malloc(strlen(a) + strlen(b) + strlen(c) + strlen(d) + 1);
    strcat(s, a);
    strcat(s, b);
    strcat(s, c);
    strcat(s, d);
    return s;
}

struct agent *insertAgent(struct agent *agentlist, struct agent *agent){
    if(agentlist == NULL){
        agentlist = agent;
    }
    else{
        agent->prox = agentlist;
        agentlist->prox = NULL;
        agentlist = agent;
    }
    return (struct agent*)agentlist;
}

void writeAgent(struct agent *agentlist){

    char *fileName = stringcat(agentlist->nome, ".asl");
    FILE *g = fopen(fileName, "w+");
    fprintf(g, "%s\n\n%s\n\n%s\n\n%s", agentlist->nome, agentlist->crencas, agentlist->objetivos, agentlist->planos);
    fclose(g);
    
    agentlist = agentlist->prox;

    while (agentlist != NULL){
        writeAgent(agentlist);
        agentlist = agentlist->prox;
    }
}

void yyerror(char *s, ...){
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

int main(int argc, char *argv[]){
    int i;

    if (argc < 2){  /* stdin é lida */
        yyparse();
        return 0;
    }
    for(i = 1; i < argc; i++){ 

        FILE *f = fopen(argv[i], "r");

        if(!f){
            perror(argv[i]);
            return(1);
        }
        yyrestart(f);
        yylineno = 1;
        yyparse();
        fclose(f);
    }
    return 0;
}