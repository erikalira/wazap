#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "menus.h"

void menu_agenda()
{
    printf("\t A G E N D A\n\n");
    printf("MENU\n\n");
    printf("1: Incluir contato\n");
    printf("2: Lista de contatos\n");
    printf("3: Remover contato\n");
    printf("4: SAIR!!!\n\n");
}

void cabecalho_zap()
{
    system("cls");
    printf("\n\t\tZ A P\n\n");
}

void menu_login()
{
    printf("1: Login\n");
    printf("2: Criar conta\n");
    printf("3: SAIR!!!\n\n");
}
