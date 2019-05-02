#ifndef AGENDA_H_INCLUDED
#define AGENDA_H_INCLUDED

typedef struct pessoa{
    char nome[40];
    char telefone[20];
    char ip[20];
} tPessoa;

struct pessoa p[50];
int contador;

//FUNCOES

void agenda();

void incluir_pessoa(tPessoa p[], int *contador);

void listar_pessoas();

void remover_pessoa(tPessoa p[], int *contador);

void editar_pessoa(tPessoa p[]);

#endif // AGENDA_H_INCLUDED
