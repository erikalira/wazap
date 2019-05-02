#include "headers.h"


void agenda_grupo() {
    int op;
    do{
        cabecalho_zap();
        printf("\t GERENCIAR GRUPOS\n\n");
        printf("1: Criar grupo\n");
        printf("2: Editar grupo\n");
        printf("3: Remover grupo\n");
        printf("4: Lista de grupos\n");
        printf("5: voltar ao menu principal!!!\n\n");

        printf("digite opcao:");
        scanf("%d",&op);

        switch(op){
            case 1:incluir_grupo(g, &contador_grupo);
                break;
            case 2:editar_grupo(g);
                break;
            case 3:remover_grupo(g, &contador_grupo);
                break;
            case 4:listar_grupos(g);
                break;
            default:
                break;
        }
        if(op!=5){
           system("pause");
        }

        system("cls");
    }while(op!=5);

    printf("\n\n\tSaindo da agenda de grupos!\n\n\n");
}


void incluir_grupo(tGrupo g[], int *contador_grupo){
    int i=0;
    int j;
    FILE *arquivo;
    FILE *temp;

    arquivo = fopen(banco_user_logado_grupo, "r+");

    if(arquivo==0){
        printf("arquivo nao foi aberto");;
    }

    printf("\n\n\tINCLUIR GRUPO\n");

    printf("Nome do grupo:");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", g[*contador_grupo].nome_grupo);

    printf("Tamanho do grupo: ");
    scanf("%d", &g[*contador_grupo].tamanho_grupo);

    for(j=0;j<g[*contador_grupo].tamanho_grupo;j++){
        printf("Nome do user %d: ", j+1);
        setbuf(stdin,NULL);
        scanf("%[^\n]s", g[*contador_grupo].nome[j]);

        printf("IP do user %d: ", j+1);
        setbuf(stdin,NULL);
        scanf("%[^\n]s", g[*contador_grupo].ip[j]);
    }

    printf("\n\nnome do grupo incluido:%s\n",g[*contador_grupo].nome_grupo);
    (*contador_grupo)++;
    printf("No de grupos: %d\n",(*contador_grupo)-1);

    temp = fopen("dados/temp.txt", "w");
    while( i < (*contador_grupo) ){
        fprintf(temp, "%s %d\n", g[i].nome_grupo, g[i].tamanho_grupo);
        for(j=0; j < g[i].tamanho_grupo ; j++ ){
            fprintf(temp, "%s %s\n", g[i].nome[j], g[i].ip[j]);
        }
        i++;
    }

    fclose(arquivo);
    fclose(temp);

    //remove o arquivo atual e renomeia o temporario para o nome do arquivo original
    remove(banco_user_logado_grupo);
    rename("dados/temp.txt", banco_user_logado_grupo);
}


void listar_grupos(tGrupo g[]){
    int i,j;
    printf("\n\n\tLISTA DE GRUPOS\n\n");
    printf("contador: %d grupos\n\n",contador_grupo-1);
    for(i=1;i<contador_grupo;i++){
        printf("GRUPO %d: %s\n",i, g[i].nome_grupo);
        printf("tamanho: %d membros\n", g[i].tamanho_grupo);
        for(j=0 ;    j < g[i].tamanho_grupo    ;   j++){
            printf("(%d)  nome: %s", j+1,g[i].nome[j]);
            printf("\tip: %s\n", g[i].ip[j]);
        }
        printf("\n");
    }
}


void remover_grupo(tGrupo g[], int *contador_grupo){
    char remover[40];
    int i,j;

    FILE *arquivo;
    FILE *temp;

    arquivo = fopen(banco_user_logado_grupo, "r+");

    printf("\n\n\tREMOVER GRUPO\n");
    printf("Nome: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", remover);

    for(i=1;i<=*contador_grupo;i++){
        if (strcmp(remover, g[i].nome_grupo) == 0){
            printf("\n\ngrupo achado e removido: %s\n", g[i].nome_grupo);

            strcpy(g[i].nome_grupo,g[(*contador_grupo)-1].nome_grupo);
            g[i].tamanho_grupo = g[(*contador_grupo)-1].tamanho_grupo;

            for(j=0;j<  g[i].tamanho_grupo  ;   j++){
                strcpy(g[i].nome[j] ,g[(*contador_grupo)-1].nome[j]);
                strcpy(g[i].ip[j] ,g[(*contador_grupo)-1].ip[j]);
            }
            (*contador_grupo)--;

            break;
        }
    }

    temp = fopen("dados/temp.txt", "w+");
    i=0;
    while( i < (*contador_grupo) ){
        fprintf(temp, "%s %d\n", g[i].nome_grupo, g[i].tamanho_grupo);
        for(j=0; j < g[i].tamanho_grupo ; j++ ){
            fprintf(temp, "%s %s\n", g[i].nome[j], g[i].ip[j]);
        }
        i++;
    }

    fclose(arquivo);
    fclose(temp);

    //remove o arquivo atual e renomeia o temporario para o nome do arquivo original
    remove(banco_user_logado_grupo);
    rename("dados/temp.txt", banco_user_logado_grupo);
}

void editar_grupo(tGrupo g[]){
    char editar[40];
    int i,j;

    FILE *arquivo;
    FILE *temp;

    arquivo = fopen(banco_user_logado_grupo, "r+");

    printf("\n\n\tEDITAR GRUPO\n");
    printf("Nome: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", editar);

    for(i=1;i<=contador_grupo;i++){
        if (strcmp(editar, g[i].nome_grupo) == 0){
            printf("\n\ngrupo achado: %s\n", g[i].nome_grupo);
            printf("Nome do grupo:");
            setbuf(stdin,NULL);
            scanf("%[^\n]s", g[i].nome_grupo);

            printf("Tamanho do grupo: ");
            scanf("%d", &g[i].tamanho_grupo);

            for(j=0 ;    j<g[i].tamanho_grupo ;   j++){
                printf("Nome do user %d: ", j+1);
                setbuf(stdin,NULL);
                scanf("%[^\n]s", g[i].nome[j]);

                printf("IP do user %d: ", j+1);
                setbuf(stdin,NULL);
                scanf("%[^\n]s", g[i].ip[j]);
            }
            break;
        }
    }

    temp = fopen("dados/temp.txt", "w+");
    i=0;
    while( i < contador_grupo ){
        fprintf(temp, "%s %d\n", g[i].nome_grupo, g[i].tamanho_grupo);
        for(j=0; j < g[i].tamanho_grupo ; j++ ){
            fprintf(temp, "%s %s\n", g[i].nome[j], g[i].ip[j]);
        }
        i++;
    }

    fclose(arquivo);
    fclose(temp);

    //remove o arquivo atual e renomeia o temporario para o nome do arquivo original
    remove(banco_user_logado_grupo);
    rename("dados/temp.txt", banco_user_logado_grupo);
}
