extern int yylineno;
void yyerror(char *s, ...);
int yyparse(void);
int yylex(void);
void yyrestart();

// struct list {
//   struct agent *l;
// };

// struct listAgents{
//     struct agent agent;
//     struct agent *prox;
// };


struct agent {
    char *nome;
    struct crencas *crenca;
    struct planos *planos;
    struct objetivos *objetivos;
    struct agent *prox;
};

struct crencas {
    char *crenca;
    struct crencas *prox;
};

struct objetivos {
    char *objetivo;
    struct objetivos *prox;
};

struct planos {
    char *eventoGatilho;
    char *contexto;
    char *corpo;
    struct planos *prox;
};
struct crencas *newCrenca(char *crenca);

struct crencas *insertCrenca(struct crencas *crencalist, struct crencas *crenca);

struct objetivos *newObjetivo(char *objetivo);

struct objetivos *insertObjetivo(struct objetivos *objetivolist, struct objetivos *objetivo);

struct planos *newPlano(char *plano);

struct planos *insertPlano(struct planos *planolist, struct planos *plano);

struct agent *newAgent(char* nome, char* crencas, char* planos, char* objetivos);

struct agent *insertAgent(struct agent *agentlist, struct agent *agent);

char * stringcat(char *a, char *b);

char * threecat(char *a, char *b, char *c);

char * fourcat(char *a, char *b, char *c, char *d);

void agentfree(struct agent *a);