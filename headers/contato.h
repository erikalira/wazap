#ifndef AGENDA_H_INCLUDED
#define AGENDA_H_INCLUDED

typedef struct pessoa{
    char nome[40];
    char telefone[20];
    char ip[20];
} tPessoa;

struct pessoa p[50];
char banco_user_logado[50];
int contador;

//FUNCOES

void agenda();

void incluir_pessoa(tPessoa p[], int *contador);

void listar_pessoas(tPessoa p[], int contador);

void remover_pessoa(tPessoa p[], int *contador);



#endif // AGENDA_H_INCLUDED
