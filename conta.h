#ifndef CADASTRO_H_INCLUDED
#define CADASTRO_H_INCLUDED

typedef struct usuario{
    char nome[20];
    char username[20];
    char senha[20];
} tUsuario;

void cadastro_usuario(tUsuario u[], int *contador_cadastro);

void banco_usuarios(char op[]);

void login (tUsuario u[]);

#endif // CADASTRO_H_INCLUDED
