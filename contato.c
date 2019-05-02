#include "headers.h"

void agenda() {
    int op;
    do{
        cabecalho_zap();
        //MENU
        printf("\t GERENCIAR CONTATOS\n\n");
        printf("1: Incluir contato\n");
        printf("2: Editar contato\n");
        printf("3: Remover contato\n");
        printf("4: Lista de contatos\n");
        printf("5: voltar ao menu principal!!!\n\n");

        printf("digite opcao:");
        scanf("%d",&op);

        switch(op){
            case 1:incluir_pessoa(p, &contador);
                break;
            case 2:editar_pessoa(p);
                break;
            case 3:remover_pessoa(p,&contador);
                break;
            case 4:listar_pessoas();
                break;
            default:
                break;
        }
        if(op!=5){
           system("pause");
        }

        system("cls");
    }while(op!=5);

    printf("\n\n\tSaindo da agenda de contatos!\n\n\n");
}


void incluir_pessoa(tPessoa p[], int *contador){

    int i=0;
    FILE *arquivo;
    FILE *temp;

    arquivo = fopen(banco_user_logado_contato, "r+");

    if(arquivo==0){
        printf("arquivo nao foi aberto");;
    }

    printf("\n\n\tINCLUIR CONTATO\n");

    printf("Nome: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", p[*contador].nome);

    printf("Telefone: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", p[*contador].telefone);

    printf("IP: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", p[*contador].ip);

    printf("\n\nnome da pessoa incluida:%s\n",p[*contador].nome);
    (*contador)++;
    printf("No de contatos: %d\n",(*contador)-1);

    temp = fopen("dados/temp.txt", "w+");

    while( i < (*contador) ){
        fprintf(temp, "%s %s %s\n", p[i].nome, p[i].telefone, p[i].ip);
        i++;
    }

    fclose(arquivo);
    fclose(temp);

    //remove o arquivo atual e renomeia o temporario para o nome do arquivo original
    remove(banco_user_logado_contato);
    rename("dados/temp.txt", banco_user_logado_contato);
}


void listar_pessoas(){
    int i;
    printf("\n\n\tLISTA DE CONTATOS\n\n");
    for(i=1;i<contador;i++){
        printf("CONTATO %d:\n",i);
        printf("nome: %s\n", p[i].nome);
        printf("telefone: %s\n", p[i].telefone);
        printf("ip: %s\n", p[i].ip);
        printf("\n");
    }
    printf("\n\n");
}


void remover_pessoa(tPessoa p[], int *contador){
    char remover[40];
    int i;

    int k=0;

    FILE *arquivo;
    FILE *temp;

    arquivo = fopen(banco_user_logado_contato, "r+");

    printf("\n\n\tREMOVER CONTATO\n");
    printf("Nome: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", remover);

    for(i=0;i<=*contador;i++){
        if (strcmp(remover, p[i].nome) == 0){
            printf("\n\npessoa achada e removida: %s\n", p[i].nome);

            strcpy(p[i].nome,p[(*contador)-1].nome);
            p[(*contador)-1].nome[0]='\0';

            strcpy(p[i].telefone ,p[(*contador)-1].telefone);
            p[(*contador)-1].telefone[0]='\0';

            strcpy(p[i].ip ,p[(*contador)-1].ip);
            p[(*contador)-1].ip[0]='\0';

            (*contador)--;
            break;
        }
    }

    temp = fopen("dados/temp.txt", "w+");

    while( k < (*contador) ){
        fprintf(temp, "%s %s %s\n", p[k].nome, p[k].telefone, p[k].ip);
        k++;
    }

    fclose(arquivo);
    fclose(temp);

    //remove o arquivo atual e renomeia o temporario para o nome do arquivo original
    remove(banco_user_logado_contato);
    rename("dados/temp.txt", banco_user_logado_contato);
}


void editar_pessoa(tPessoa p[]){
    char editar[40];
    int i;

    int k=0;

    FILE *arquivo;
    FILE *temp;
    FILE *criar_banco;

    char arquivo_usuario[40];

    arquivo = fopen(banco_user_logado_contato, "r+");

    printf("\n\n\tEDITAR CONTATO\n");
    printf("Nome: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", editar);

    for(i=0;i<=contador;i++){
        if (strcmp(editar, p[i].nome) == 0){
            printf("Nome: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]s", p[i].nome);

            printf("Telefone: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]s", p[i].telefone);

            printf("IP: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]s", p[i].ip);
            break;
        }
    }

    temp = fopen("dados/temp.txt", "w+");

    while( k < (contador) ){
        fprintf(temp, "%s %s %s\n", p[k].nome, p[k].telefone, p[k].ip);
        k++;
    }

    fclose(arquivo);
    fclose(temp);

    //remove o arquivo atual e renomeia o temporario para o nome do arquivo original
    remove(banco_user_logado_contato);
    rename("dados/temp.txt", banco_user_logado_contato);

    //------**CRIA ARQUIVOS PARA ARMAZENAR CONTATOS DO USUARIO**----------

    //armazena o diretorio que o arquivo deve ser criado
    sprintf( arquivo_usuario, "dados/contatos_%s.txt", u[contador_cadastro].username);

    //cria o arquivo para salvar os contatos do usuario
    criar_banco = fopen(arquivo_usuario, "w");

    //salva um primeiro contato teste para padronizar
    fprintf(criar_banco, "nome telefone ip\n");

    fclose(criar_banco);
    //--------------ARQUIVO CRIADO---------------------------


    //--------**CRIA ARQUIVOS PARA ARMAZENAR GRUPOS**----------

    //armazena o diretorio que o arquivo deve ser criado
    sprintf( arquivo_usuario, "dados/grupos_%s.txt", u[contador_cadastro].username);

    //cria o arquivo para salvar grupos usuario
    criar_banco = fopen(arquivo_usuario, "w");

    //salva uma primeira linha com 0 para evitar erro
    fprintf(criar_banco, "grupo 2\nfulano 2131\nciclano 12312\n");

    fclose(criar_banco);
    //---------------ARQUIVO CRIADO---------------------------

}
