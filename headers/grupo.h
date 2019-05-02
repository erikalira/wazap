#ifndef GRUPO_H_INCLUDED
#define GRUPO_H_INCLUDED

typedef struct grupo{
    char nome[30];
    char nomes[10][30];
    char ips[10][20];
} tGrupo;

struct grupo g[50];
int contador_grupo;

//FUNCOES

void agenda_grupo();

void incluir_grupo(tGrupo g[], int *contador_grupo);

void listar_grupos(tGrupo g[], int contador_grupo);

void remover_grupo(tGrupo g[], int *contador_grupo);

#endif // GRUPO_H_INCLUDED
