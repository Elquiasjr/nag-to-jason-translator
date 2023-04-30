extern int yylineno;
void yyerror(char *s, ...);
int yyparse(void);


struct crencas{
    char *crenca;
    struct crencas *prox;
};

struct objetivos{
    char *objetivo;
    struct objetivos *prox;
};

struct corpo{
    char *corpo;
    struct corpo *prox;
};
struct content{
    char *eventoGatilho;
    char *contexto;
    struct corpo *corpo;
};
struct planos{
    char *name;
    struct content *conteudo;
    struct planos *prox;
};

struct agent{
    char *nome;
    struct crencas *crencas;
    struct objetivos *objetivos; 
    struct planos *planos;
    struct agent *prox;
};

struct crencas *newCrenca(char *crenca);
struct crencas *insertCrenca(struct crencas *crencalist, struct crencas *crenca);
struct objetivos *newObjetivo(char *objetivo);
struct objetivos *insertObjetivo(struct objetivos *objetivolist, struct objetivos *objetivo);
struct content *newContent(char *eventoGatilho, char *contexto, struct corpo *corpo);
struct corpo *newCorpo(char *corpo);
struct corpo *insertCorpo(struct corpo *corpolist, struct corpo *corpo);
struct planos *newPlano(char *name, struct content *content);
struct planos *insertPlano(struct planos *planolist, struct planos *plano);
struct agent *newAgent(char *nome, struct crencas *crencas, struct objetivos *objetivos, struct planos *planos);
struct agent *insertAgent(struct agent *agentlist, struct agent *agent);
void writeAgent(struct agent *agentlist);
char * stringcat(char *a, char *b);
char * threecat(char *a, char *b, char *c);