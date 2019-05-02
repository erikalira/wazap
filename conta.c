/*
problemas:

1. quando coloca um nome composto(ex: erika lira), o arquivo reconhece o segundo nome como o proximo dado.
soluções possiveis:
a) colocar um outro caractere no espaço do nome para a leitura do fprintf ser corrigida
ex: nome ="erika lira" salvar no arquivo como "erika.lira"
b) salvar no arquivo cada linha uma informacao diferente
ex ao inves de: erika lira 88232-23222 127.0.0.1
salvar como:
erika lira
88232-23222
127.0.0.1
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

    //----***PEDIR AO USUARIO SEUS DADOS***----
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
    //-------------------------------------------


    //------**CRIA ARQUIVOS PARA ARMAZENAR CONTATOS DO USUARIO**----------

    //armazena o diretorio que o arquivo deve ser criado
    sprintf( arquivo_usuario, "dados/contatos_%s.txt", u[*contador_cadastro].username);

    //cria o arquivo para salvar os contatos do usuario
    criar_banco = fopen(arquivo_usuario, "w");

    //salva um primeiro contato teste para padronizar
    fprintf(criar_banco, "nome telefone ip\n");

    fclose(criar_banco);
    //--------------ARQUIVO CRIADO---------------------------


    //--------**CRIA ARQUIVOS PARA ARMAZENAR GRUPOS**----------

    //armazena o diretorio que o arquivo deve ser criado
    sprintf( arquivo_usuario, "dados/grupos_%s.txt", u[*contador_cadastro].username);

    //cria o arquivo para salvar grupos usuario
    criar_banco = fopen(arquivo_usuario, "w");

    //salva uma primeira linha com 0 para evitar erro
    fprintf(criar_banco, "grupo 2\nfulano 2131\nciclano 12312\n");

    fclose(criar_banco);
    //---------------ARQUIVO CRIADO---------------------------


    //--------------------***CONFIRMACAO DE CADASTRO***-------------------
    printf("\n\nnome da pessoa incluida:%s\n",u[*contador_cadastro].nome);
    (*contador_cadastro)++;
    printf("No de Usuarios cadastrados:%d\n", (*contador_cadastro)-1  );
    //--------------------------------------------------------------------


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
        if( strcmp( username, u[i].username ) == 0  ){
            if(   strcmp( senha, u[i].senha ) == 0  ){
                printf("LOGAR!!!");
                logado( u[i].username );
                no_user=1;
            }
        }
    }

    if(no_user==0)
        printf("\n\nUSUARIO E/OU SENHA INCORRETX\n\n");

};


void logado( char user[] ) {
    contador=0;
    contador_grupo=0;
    int op;
    FILE *arquivo;
    FILE *arq;

    //---------------***ARMAZENA OS CONTATOS NA ESTRUTURA***---------
    sprintf( banco_user_logado_contato, "dados/contatos_%s.txt", user);
    arquivo = fopen( banco_user_logado_contato , "r+"); //ABRIR ARQUIVO

    if(arquivo == NULL){
        printf("arquivo nao foi aberto!\n");
    }

    while(!feof(arquivo)){
        fscanf(arquivo, "%s %s %s ", p[contador].nome, p[contador].telefone, p[contador].ip);
        contador++;
    }

    fclose(arquivo); //FECHAR ARQUIVO
    //---------------ARMAZENADO---------

    //---------------***ARMAZENA OS GRUPOS NA ESTRUTURA***---------
    sprintf( banco_user_logado_grupo, "dados/grupos_%s.txt", user);
    arq = fopen( banco_user_logado_grupo , "r+"); //ABRIR ARQUIVO

    if(arq == NULL){
        printf("arquivo nao foi aberto!\n");
    }
    int i;
    while(!feof(arq)){
        fscanf(arq, "%s %d ", g[contador_grupo].nome_grupo, &g[contador_grupo].tamanho_grupo);
        for(i=0; i<g[contador_grupo].tamanho_grupo ; i++ ){
            fscanf(arq, "%s %s ", g[contador_grupo].nome[i], g[contador_grupo].ip[i]);
        }
        contador_grupo++;
    }

    fclose(arq); //FECHAR ARQUIVO
    //---------------ARMAZENADO---------



    do{
        printf("Bem vindx, %s\n\n", user);

        cabecalho_zap();

        if(  strcmp(modo,"cliente") == 0  ){
            printf("1-Gerenciar contas\n");
            printf("2-Gerenciar contatos \n");
            printf("3-Gerenciar grupos\n");
            printf("4-Iniciar conversa\n");
            printf("5-Sair da conta!!!\n\n");
        }else if(  strcmp(modo,"servidor") == 0  ){
            printf("1-Gerenciar contas\n");
            printf("2-Gerenciar contatos \n");
            printf("3-Gerenciar grupos\n");
            printf("4-Participar de uma conversa\n");
            printf("5-Sair da conta!!!\n\n");

        }else{
            printf("Nao ACHOU NENUMA OPCAO DE MODDOO!!!");
        }

        printf("digite opcao:");
        scanf("%d",&op);

        switch(op){
            case 1:      contas();   //Gerenciar contas
                break;
            case 2:      agenda();      //Gerenciar contatos
                break;
            case 3:      agenda_grupo();//Gerenciar grupos
                break;
            case 4:
                if(  strcmp(modo,"cliente") == 0  ){
                    escolher_conversa_client(); //Iniciar conversa
                }if(  strcmp(modo,"servidor") == 0  ){
                    escolher_conversa_server(); //Participar de conversa
                }
                break;
            default:
                break;
        }

        system("cls");


    }while(op!=5);
    printf("\n\nUSUARIO DESLOGADO!\n\n\n");
}


void contas(){
    int op;
    do{
        cabecalho_zap();
        //MENU
        printf("\t GERENCIAR CONTAS\n\n");
        printf("1-Criar conta\n");
        printf("2-Editar conta\n");
        printf("3-Excluir conta\n");
        printf("4-Lista de contas\n");
        printf("5-Voltar\n\n");

        printf("digite opcao:");
        scanf("%d", &op);

        switch(op){
            case 1:
                //CRIAR CONTA
                banco_usuarios("cadastro");
                break;
            case 2:
                //EDITAR CONTA
                editar_cadastro(u);
                break;
            case 3:
                //EXCLUI CONTA
                remover_cadastro(u, &contador_cadastro);
                break;
            case 4:
                //LISTA DE CONTAS
                listar_usuarios();

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
        printf("CONTA %d:\n",i);
        printf("nome: %s\n", u[i].nome);
        printf("username: %s\n", u[i].username);
        printf("\n");
    }
    printf("\n\n");
}


void remover_cadastro(tUsuario u[], int *contador_cadastro){
    char remover[40];
    int i;
    int k=0;

    FILE *arquivo;
    FILE *temp;

    arquivo = fopen("dados/contas.txt", "r+");

    printf("\n\n\tREMOVER CADASTRO\n");
    printf("Username: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", remover);

    for(i=0;i<=*contador_cadastro;i++){
        if (strcmp(remover, u[i].username) == 0){
            printf("\n\npessoa achada e removida: %s\n", u[i].nome);

            strcpy(p[i].nome,u[(*contador_cadastro)-1].nome);
            u[(*contador_cadastro)-1].nome[0]='\0';

            strcpy(u[i].username ,u[(*contador_cadastro)-1].username);
            u[(*contador_cadastro)-1].username[0]='\0';

            strcpy(u[i].senha ,u[(*contador_cadastro)-1].senha);
            u[(*contador_cadastro)-1].senha[0]='\0';

            (*contador_cadastro)--;
            break;
        }
    }

    temp = fopen("dados/temp.txt", "w+");

    while( k < (*contador_cadastro) ){
        fprintf(temp, "%s %s %s\n", u[k].nome, u[k].username, u[k].senha);
        k++;
    }

    fclose(arquivo);
    fclose(temp);

    //remove o arquivo atual e renomeia o temporario para o nome do arquivo original
    remove("dados/contas.txt");
    rename("dados/temp.txt", "dados/contas.txt");
}

void editar_cadastro(tUsuario u[]){
    char editar[40];
    int i;
    int k=0;

    FILE *arquivo;
    FILE *temp;

    arquivo = fopen("dados/contas.txt", "r+");

    printf("\n\n\tEDITAR CADASTRO\n");
    printf("Username: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", editar);

    for(i=0;i<=contador_cadastro;i++){
        if (strcmp(editar, u[i].username) == 0){
            printf("\n\npessoa achada: %s\n", u[i].nome);

            printf("Nome: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]s", u[i].nome);

            printf("Usuario: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]s", u[i].username);

            printf("Senha: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]s", u[i].senha);
            break;
        }
    }

    temp = fopen("dados/temp.txt", "w+");

    while( k < contador_cadastro ){
        fprintf(temp, "%s %s %s\n", u[k].nome, u[k].username, u[k].senha);
        k++;
    }

    fclose(arquivo);
    fclose(temp);

    //remove o arquivo atual e renomeia o temporario para o nome do arquivo original
    remove("dados/contas.txt");
    rename("dados/temp.txt", "dados/contas.txt");
}
