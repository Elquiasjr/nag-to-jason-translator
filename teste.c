#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dicionario{
    char *palavra;
    char *traducao;
    struct dicionario *prox;
};

char * concatenaTres(char *s1, char *s2, char *s3){
    char *s4 = (char*) malloc(strlen(s1) + strlen(s2) + strlen(s3) + 1);
    strcat(s4, s1);
    strcat(s4, s2);
    strcat(s4, s3);

    return s4;
}

int main(){

// crie parte do codigo que une dois ponteiros de char e retorna um ponteiro de char

    char *s1 = "bob";
    char *s2 = ".asl";
    char *s3 = "!";
    
    char *s4 = concatenaTres(s1, s2, s3);
    char *s5 = s4;
    char *s6 = "alo";

    char *s7 = concatenaTres(s4, s5, s6);

    printf("%s\n", s7);
    // struct dicionario *d1 = (struct dicionario*) malloc(sizeof(struct dicionario));

    // d1->palavra = s4;
    // printf("%s\n", d1->palavra);


    return 0;


}