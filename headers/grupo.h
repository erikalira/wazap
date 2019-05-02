#ifndef GRUPO_H_INCLUDED
#define GRUPO_H_INCLUDED

typedef struct grupo{
    char nome_grupo[30];
    int tamanho_grupo;
    char nome[10][30];
    char ip[10][20];
} tGrupo;

struct grupo g[50];
int contador_grupo;

//FUNCOES

void agenda_grupo();

void incluir_grupo(tGrupo g[], int *contador_grupo);

void listar_grupos(tGrupo g[]);

void remover_grupo(tGrupo g[], int *contador_grupo);

void editar_grupo(tGrupo g[]);

#endif // GRUPO_H_INCLUDED
