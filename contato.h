#ifndef AGENDA_H_INCLUDED
#define AGENDA_H_INCLUDED

typedef struct pessoa{
    char nome[40];
    char telefone[20];
    char ip[20];
} tPessoa;



void incluir_pessoa(tPessoa p[], int *contador);

void listar_pessoas(tPessoa p[], int contador);

void remover_pessoa(tPessoa p[], int *contador);

void agenda(char user[]);

#endif // AGENDA_H_INCLUDED
