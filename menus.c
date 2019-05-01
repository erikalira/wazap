#include "headers.h"

void menu_agenda()
{
    printf("\t A G E N D A\n\n");
    printf("1: Incluir contato\n");
    printf("2: Lista de contatos\n");
    printf("3: Remover contato\n");
    printf("4: voltar ao menu principal!!!\n\n");
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
    printf("3: SAIR DA APLICACAO!!!\n\n");
}

void menu_logado()
{
    printf("1-Gerenciar contas\n");
    printf("2-Gerenciar contatos \n");
    printf("3-Gerenciar grupos (EM CONSTRUCAO)\n");
    printf("4-Iniciar conversa\n");
    printf("5-Sair da conta!!!\n\n");
}

void menu_logado_server()
{
    printf("1-Gerenciar contas\n");
    printf("2-Gerenciar contatos \n");
    printf("3-Gerenciar grupos (EM CONSTRUCAO)\n");
    printf("4-Participar de uma conversa\n");
    printf("5-Sair da conta!!!\n\n");
}

void menu_conversas()
{
    printf("\t INICIAR CONVERSA\n\n");
    printf("1-Iniciar conversa com contato\n");
    printf("2-Iniciar conversa com grupo (EM CONSTRUCAO)\n");
    printf("3-Voltar\n\n");
}


void menu_contas(){
    printf("\t GERENCIAR CONTAS\n\n");
    printf("1-Criar conta\n");
    printf("2-Editar conta (EM CONSTRUCAO)\n");
    printf("3-Lista de contas\n");
    printf("4-Excluir conta(EM CONSTRUCAO)\n");
    printf("5-Voltar\n\n");
}
