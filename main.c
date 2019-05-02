#include "headers.h"

int main(){

    do{
        cabecalho_zap();
        printf("modo: cliente ou servidor\n");
        printf("digite opcao:");

        setbuf(stdin,NULL);
        scanf("%[^\n]s", modo); //usar esse modo de pegar string como padrao pois ele nao buga!!! e da pra fazer strcmp safe

        if( strcmp(modo,"cliente")!=0 && strcmp(modo,"servidor")!=0  ){
            printf("\nOpcao incorreta!! Digite cliente ou servidor em portugues\n");
            system("pause");
        }
    }while( strcmp(modo,"cliente")!=0 && strcmp(modo,"servidor")!=0  );
    printf("Entrando no modo %s\n", modo);
    system("pause");

    int op;
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
    printf("\n\n\n\n\tZAP FINALIZADO!!!\n\n\n\n\n");
    system("pause");

    return 0;
}
