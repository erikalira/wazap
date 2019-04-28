#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "conta.h"
#include "contato.h"
#include "menus.h"

int main(){

    do{
        cabecalho_zap();
        menu_login();
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
    printf("\n\n\n\n\t\tZAP FINALIZADO!!!\n\n\n\n\n");
    system("pause");

    return 0;
}
