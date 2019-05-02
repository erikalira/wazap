#include "headers.h"

void cabecalho_zap()
{
    system("cls");
    printf("\n\t\tZ A P NUTELLA (%s)\n\n", modo);
}

int main(int argc, char *argv[]){
    // MODO CLIENTE OU SERVIDOR
    if (argc < 2) {
       fprintf(stderr,"faltou dizer se eh servidor ou cliente\n");
       exit(0);
    }

    if( strcmp("servidor",argv[1])  != 0  &&  strcmp("cliente",argv[1])  != 0  ){
        fprintf(stderr,"modo invalido!! dizer se eh servidor ou cliente\n");
        exit(0);
    }

    strcpy(modo, argv[1]);

    int op;
    do{
        cabecalho_zap();
        //MENU
        printf("1: Login\n");
        printf("2: Criar conta\n");
        printf("3: SAIR DA APLICACAO!!!\n\n");

        printf("digite opcao:");
        scanf("%d", &op);

        switch(op){
            case 1:
                //LOGIN
                banco_usuarios("login");
                break;
            case 2:
                //CRIAR CONTA
                banco_usuarios("cadastro");
                break;
            default:
                break;
        }
        if(op!=3){
           system("pause");
        }

        system("cls");

    }while(op!=3);

    cabecalho_zap();
    printf("\n\n\n\n\tZAP FINALIZADO!!!\n\n\n\n\n");
    system("pause");

    return 0;
}
