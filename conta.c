/*
problemas:

1. quando coloca um nome composto(ex: erika lira), o arquivo reconhece o segundo nome como o proximo dado.
soluções possiveis:
a) colocar um outro caractere no espaço do nome para a leitura do fprintf ser corrigida
ex: nome ="erika lira" salvar no arquivo como "erika.lira"

2.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "conta.h"
#include "contato.h"
#include "menus.h"

void cadastro_usuario(tUsuario u[], int *contador_cadastro){

    int i=0;
    char arquivo_usuario[40];

    FILE *arquivo;
    FILE *temp;
    FILE *criar_banco;

    arquivo = fopen("dados/contas.txt", "r+");

    //---------------***PEDIR AO USUARIO SEUS DADOS***-------------
    printf("\tCADASTRO USUARIO\n\n");

    printf("Nome: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", u[*contador_cadastro].nome);

    printf("Usuario: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", u[*contador_cadastro].username);

    printf("Senha: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", u[*contador_cadastro].senha);
    //-------------------------------------------------------------

    //---------------***CRIA UM ARQUIVO PARA ARMAZENAR CONTATOS DO USUARIO***-------------
    //armazena o diretorio que o arquivo deve ser criado
    sprintf( arquivo_usuario, "dados/contatos_%s.txt", u[*contador_cadastro].username);

    //cria o arquivo para salvar os contatos do usuario
    criar_banco = fopen(arquivo_usuario, "w");

    //salva um primeiro contato teste para padronizar
    fprintf(criar_banco, "nome telefone ip\n");

    fclose(criar_banco);
    //-----------------------------ARQUIVO CRIADO---------------------------


    //--------------------***CONFIRMACAO DE CADASTRO***-----------------------
    printf("\n\nnome da pessoa incluida:%s\n",u[*contador_cadastro].nome);
    (*contador_cadastro)++;
    printf("tamanho lista:%d\n",*contador_cadastro);
    //-------------------------------------------------------------------------


    //-------------****SALVA OS DADOS NO ARQUIVO*****--------------------------

    //cria arquivo temporario
    temp = fopen("dados/temp.txt", "w+");

    while( i < (*contador_cadastro) ){
        fprintf(temp, "%s %s %s\n",     u[i].nome,
                                        u[i].username,
                                        u[i].senha);
        i++;
    }

    fclose(arquivo);
    fclose(temp);

    //remove o arquivo atual e renomeia o temporario para o nome do arquivo original
    remove("dados/contas.txt");
    rename("dados/temp.txt", "dados/contas.txt");
    //---------------------DADOS SALVOS NO ARQUIVO--------------------------------

    printf("\n\n\tteste: CADASTRADO COM SUCESSO!\n\n\n");
    //system("pause");
}


void banco_usuarios(char op[]) {
    int contador_cadastro=0;
    struct usuario u[50];
    FILE *arquivo;

    arquivo = fopen("dados/contas.txt", "r+");

    if(arquivo == NULL){
        printf("arquivo nao foi aberto!\n");
    }

    while(!feof(arquivo)){
        fscanf(arquivo, "%s %s %s\n",       u[contador_cadastro].nome,
                                            u[contador_cadastro].username,
                                            u[contador_cadastro].senha);
        contador_cadastro++;
    }

    fclose(arquivo);

    cabecalho_zap();

    if(strcmp(op,"cadastro")==0){
        cadastro_usuario(u, &contador_cadastro);
    }else if(strcmp(op,"login")==0){
        login (u);
    }
}


void login (tUsuario u[]){
    printf("\tLOGAR NA CONTA\n\n");
//
//    printf("Nome: ");
//    setbuf(stdin,NULL);
//    scanf("%[^\n]s", u[*contador_cadastro].nome);
//
//    printf("Usuario: ");
//    setbuf(stdin,NULL);
//    scanf("%[^\n]s", u[*contador_cadastro].username);
//
//    printf("Senha: ");
//    setbuf(stdin,NULL);
//    scanf("%[^\n]s", u[*contador_cadastro].senha);
};
