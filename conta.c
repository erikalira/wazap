/*
problemas:

1. quando coloca um nome composto(ex: erika lira), o arquivo reconhece o segundo nome como o proximo dado.
soluções possiveis:
a) colocar um outro caractere no espaço do nome para a leitura do fprintf ser corrigida
ex: nome ="erika lira" salvar no arquivo como "erika.lira"

2.

*/
#include "headers.h"

void banco_usuarios(char op[]) {
    contador_cadastro=0;
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
        login (u, contador_cadastro);
    }
}


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
    printf("No de Usuarios cadastrados:%d\n", (*contador_cadastro)-1  );
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

    printf("\n\n\tUSUARIO CADASTRADO COM SUCESSO!\n\n\n");
    //system("pause");
}


void login (tUsuario u[], int contador_cadastro){
    printf("\tLOGAR NA CONTA\n\n");
    int i;
    char username[20];
    char senha[20];
    int no_user=0;

    printf("Usuario: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", username);

    printf("Senha: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", senha);

    for(i=1; i<=contador_cadastro ; i++){
        if( strcmp( username, u[i].username ) ==0  ){
            if(   strcmp( senha, u[i].senha ) ==0  ){
                printf("LOGAR!!!");
                logado(u[i].username);
                no_user=1;
            }
        }
    }

    if(no_user==0)
        printf("\n\nUSUARIO E/OU SENHA INCORRETX\n\n");

};


void logado(char user[]) {
    contador=0;
    int op;
    //struct pessoa p[50];
    FILE *arquivo;

    do{
        cabecalho_zap();

        printf("Bem vindx, %s\n\n", user);

        sprintf( banco_user_logado, "dados/contatos_%s.txt", user);

        arquivo = fopen( banco_user_logado , "r+"); //ABRIR ARQUIVO

        if(arquivo == NULL){
            printf("arquivo nao foi aberto!\n");
        }

        while(!feof(arquivo)){
            fscanf(arquivo, "%s %s %s ", p[contador].nome, p[contador].telefone, p[contador].ip);
            contador++;
        }

        fclose(arquivo); //FECHAR ARQUIVO

        menu_logado();

        printf("digite opcao:");
        scanf("%d",&op);

        switch(op){
            case 1:      contas();   //Gerenciar contas
                break;
            case 2:      agenda();      //Gerenciar contatos
                break;
            case 3:      //Gerenciar grupos
                break;
            case 4:         //Iniciar conversa
                break;
            default:
                break;
        }

        system("cls");


    }while(op!=5);
    printf("\n\n\tteste: USUARIO DESLOGADO!\n\n\n");
}


void contas(){
    int op;
    do{
        cabecalho_zap();
        menu_contas();
        printf("digite opcao:");
        scanf("%d", &op);

        switch(op){
            case 1:
                //CRIAR CONTA
                banco_usuarios("cadastro");
                break;
            case 2:
                //EDITAR CONTA

                break;
            case 3:
                //LISTA DE CONTAS
                listar_usuarios();
                break;
            case 4:
                //EXCLUI CONTA

                break;
            default:
                break;
        }
        if(op!=5){
           system("pause");
        }

        system("cls");

    }while(op!=5);


}


void listar_usuarios(){
    int i;
    cabecalho_zap();
    printf("\n\n\tLISTA DE USUARIOS\n\n");
    for(i=1;i<contador_cadastro;i++){
        printf("CONTATO %d:\n",i);
        printf("nome: %s\n", u[i].nome);
        printf("username: %s\n", u[i].username);
        printf("\n");
    }
    printf("\n\n");
}


