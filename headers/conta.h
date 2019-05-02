#ifndef CADASTRO_H_INCLUDED
#define CADASTRO_H_INCLUDED

typedef struct usuario{
    char nome[20];
    char username[20];
    char senha[20];
} tUsuario;

int contador_cadastro;

char banco_user_logado_contato[50];

char banco_user_logado_grupo[50];

struct usuario u[30];

void cadastro_usuario(tUsuario u[], int *contador_cadastro);

void banco_usuarios(char op[]);

void login (tUsuario u[], int contador_cadastro);

void logado(char user[]);

void contas();

void listar_usuarios();

void remover_cadastro(tUsuario u[], int *contador_cadastro);

#endif // CADASTRO_H_INCLUDED
