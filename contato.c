#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "conta.h"
#include "contato.h"
#include "menus.h"

void incluir_pessoa(tPessoa p[], int *contador){

    int i=0;
    FILE *arquivo;
    FILE *temp;

    arquivo = fopen("dados/agenda.txt", "r+");

    printf("\n\n\tINCLUIR PESSOA\n");

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
    printf("tamanho lista:%d\n",*contador);

    temp = fopen("dados/temp.txt", "w+");

    while( i < (*contador) ){
        fprintf(temp, "%s %s %s\n", p[i].nome, p[i].telefone, p[i].ip);
        i++;
    }

    fclose(arquivo);
    fclose(temp);

    //remove o arquivo atual e renomeia o temporario para o nome do arquivo original
    remove("dados/agenda.txt");
    rename("dados/temp.txt", "dados/agenda.txt");
}

void listar_pessoas(tPessoa p[], int contador){
    int i;
    printf("\n\n\tLISTA DE PESSOAS\n\n");
    for(i=0;i<contador;i++){
        printf("CONTATO %d:\n",i+1);
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

    arquivo = fopen("dados/agenda.txt", "r+");

    printf("\n\n\tREMOVER PESSOA\n");
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
    remove("dados/agenda.txt");
    rename("dados/temp.txt", "dados/agenda.txt");
}

void agenda() {
    int contador=0;
    struct pessoa p[50];
    FILE *arquivo;

    arquivo = fopen("dados/agenda.txt", "r+"); //ABRIR ARQUIVO

    if(arquivo == NULL){
        printf("arquivo nao foi aberto!\n");
    }

    while(!feof(arquivo)){
        fscanf(arquivo, "%s %s %s ", p[contador].nome, p[contador].telefone, p[contador].ip);
        contador++;
    }

    fclose(arquivo); //FECHAR ARQUIVO

    cabecalho_zap();

    do{
        menu_agenda();

        printf("digite opcao:");
        scanf("%d",&op);

        switch(op){
            case 1:incluir_pessoa(p,&contador);
                break;
            case 2:listar_pessoas(p,contador);
                break;
            case 3:remover_pessoa(p,&contador);
                break;
            default:
                break;
        }
        if(op!=4){
           system("pause");
        }

        system("cls");
    }while(op!=4);

    printf("\n\n\tteste: AGENDA FECHADA!\n\n\n");
    system("pause");
}
