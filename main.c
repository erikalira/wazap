#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "conta.h"
#include "contato.h"
#include "menus.h"

int main(){

    cabecalho_zap();

    do{
        menu_login();
        printf("digite opcao:");
        scanf("%d", &op);

        switch(op){
            case 1:
                //LOGIN
                printf("teste: Tem conta e quer fazer login\n");
                printf("teste: Direcionando para login\n");
                system("pause");
                banco_usuarios("login");
                break;
            case 2:
                //CRIAR CONTA
                printf("\n\nteste: Nao tem conta\n\n");
                printf("\n\n\nVamos fazer uma conta!!!\n\n");
                system("pause");
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
    printf("\n\n\n\nZAP FINALIZADO!!!\n\n\n\n\n");
    system("pause");

    return 0;
}
