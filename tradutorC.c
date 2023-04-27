#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "tradutorHeader.h"


struct crencas *newCrenca(char *crenca){
    struct crencas *newC = (struct crencas*) malloc(sizeof(struct crencas));
    
    if(newC == NULL){
        printf("Erro: falha na alocação de memória. \n");
        exit(1);
    }

    newC->crenca = crenca;
    newC->prox = NULL;

    return newC;
}

struct crencas *insertCrenca(struct crencas *crencalist, struct crencas *crenca){
    if(crenca == NULL){
        return crencalist;
    }
    struct crencas *aux = crencalist;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = crenca;
    return crencalist;
}

struct objetivos *newObjetivo(char *objetivo){
    struct objetivos *newO = (struct objetivos*) malloc(sizeof(struct objetivos));
    
    if(newO == NULL){
        printf("Erro: falha na alocação de memória. \n");
        exit(1);
    }

    newO->objetivo = objetivo;
    newO->prox = NULL;

    return newO;
}

struct objetivos *insertObjetivo(struct objetivos *objetivolist, struct objetivos *objetivo){
    if(objetivo == NULL){
        return objetivolist;
    }
    struct objetivos *aux = objetivolist;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = objetivo;
    return objetivolist;
}

struct planos *newPlano(char *name, struct content *content){

    struct planos *newP = (struct planos*) malloc(sizeof(struct planos));
    
    if(newP == NULL){
        printf("Erro: falha na alocação de memória. \n");
        exit(1);
    }
    newP->name = name;
    newP->conteudo = content;
    newP->prox = NULL;

    return newP;
}

struct content *newContent(char *eventoGatilho, char *contexto, struct corpo *corpo){
    struct content *newC = (struct content*) malloc(sizeof(struct content));
    
    if(newC == NULL){
        printf("Erro: falha na alocação de memória. \n");
        exit(1);
    }

    newC->eventoGatilho = eventoGatilho;
    newC->contexto = contexto;
    newC->corpo = corpo;

    return newC;
}

struct corpo *newCorpo(char *corpo){
    struct corpo *newC = (struct corpo*) malloc(sizeof(struct corpo));
    
    if(newC == NULL){
        printf("Erro: falha na alocação de memória. \n");
        exit(1);
    }

    newC->corpo = corpo;
    newC->prox = NULL;

    return newC;
}

struct corpo *insertCorpo(struct corpo *corpolist, struct corpo *corpo){
    if(corpo == NULL){
        return corpolist;
    }
    struct corpo *aux = corpolist;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = corpo;
    return corpolist;
}
struct planos *insertPlano(struct planos *planolist, struct planos *plano){
    if(plano == NULL){
        return planolist;
    }
    struct planos *aux = planolist;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = plano;
    return planolist;
}

struct agent* newAgent(char *nome, struct crencas *crencas, struct objetivos *objetivos, struct planos *planos){
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

    return newA;
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
    
    char* filename = stringcat(agentlist->nome, ".asl");
    FILE *fp = fopen(filename, "w");
    if(fp == NULL){
        printf("Erro: falha na abertura do arquivo. \n");
        exit(1);
    }
    struct crencas *aux = agentlist->crencas;
    while(aux != NULL){
        fprintf(fp, "%s.\n", aux->crenca);
        aux = aux->prox;
    }
    fprintf(fp, "\n");
    struct objetivos *aux2 = agentlist->objetivos;
    while(aux2 != NULL){
        fprintf(fp, "!%s.\n", aux2->objetivo);
        aux2 = aux2->prox;
    }
    fprintf(fp, "\n");
    struct planos *aux3 = agentlist->planos;
    while(aux3 != NULL){
        fprintf(fp, "+!%s: ", aux3->conteudo->eventoGatilho);
        fprintf(fp, "%s <- ", aux3->conteudo->contexto);
        struct corpo *aux4 = aux3->conteudo->corpo;
        while(aux4 != NULL){
            fprintf(fp, "%s; ", aux4->corpo);
            aux4 = aux4->prox;
        }
        aux3 = aux3->prox;
        fprintf(fp, "\n");
    }
    fclose(fp);
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