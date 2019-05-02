#include "headers.h"

#define BACKLOG_MAX 5
#define BUFFER_SIZE 128
#define EXIT_CALL_STRING "#sair"

int local_socket = 0;
int remote_socket = 0;

int remote_length = 0;
int message_length = 0;

int local_port = 0;
int remote_port = 5000;

int i;

char remote_ip[32];
char message[BUFFER_SIZE];

char contato[30];
int sem_conexao=0;

struct sockaddr_in local_address;
struct sockaddr_in remote_address;

WSADATA wsa_data;

void msg_err_exit(char *msg)
{
    fprintf(stderr, msg);
    system("PAUSE");
    sem_conexao=1;
    //exit(EXIT_FAILURE);
}

//FUNCOES PARA O CLIENT

void escolher_conversa_client (){

    int op;
    do{
        cabecalho_zap();
        menu_conversas();

        printf("digite opcao:");
        scanf("%d",&op);


        switch(op){
            case 1:     conversa_contato_client();
                break;
            case 2:     conversa_grupo_client();
                break;
            default:
                break;
        }

        system("cls");
    }while(op!=3);

//    // envia a mensagem para o servidor para sair do socket
//    if (send(remote_socket, "#sair", 155, 0) == SOCKET_ERROR)
//    {
//        WSACleanup();
//        closesocket(remote_socket);
//        msg_err_exit("send() failed\n");
//    }
}

int conversa_contato_client(){

    conectar_client();
    if(sem_conexao==1){
        sem_conexao=0;
        return 0;
    }

    printf("digite as mensagens     //para sair da conversa digite #sair\n");
    getchar();
    do
    {
        printf("digite msg: ");

        // limpa o buffer
        memset(&message, 0, BUFFER_SIZE);
        //gets(message);
        //fflush(stdin);
        setbuf(stdin,NULL);
        scanf("%[^\n]s", message);

        //message_length = strlen(message);

        // envia a mensagem para o servidor
        if (send(remote_socket, message, 115, 0) == SOCKET_ERROR)
        {
            WSACleanup();
            closesocket(remote_socket);
            msg_err_exit("send() failed\n");
        }

        if(   strcmp(message, EXIT_CALL_STRING) !=0 ){
            // limpa o buffer
            memset(&message, 0, BUFFER_SIZE);

            // recebe a mensagem do cliente
            recv(remote_socket, message, BUFFER_SIZE, 0);

            // exibe a mensagem na tela
            printf("%s: %s\n", contato, message);
        }
    }while(strcmp(message, EXIT_CALL_STRING)); // sai quando enviar um "#sair" para o servidor
    send(remote_socket, "client saiu da conversa!!", 115, 0);
    //printf("\nsaindo da conversao com o contato..\n");

    desconectar_client();
    system("PAUSE");
    return 0;
}

void conversa_grupo_client(){

}

void conectar_client(){

    if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0)
        msg_err_exit("WSAStartup() failed\n");


    printf("nome do contato:");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", contato);

    printf("Porta: ");
    scanf("%d", &remote_port);

    for(i=0;i<=contador;i++){
        if (strcmp(contato, p[i].nome) == 0){
            strcpy(remote_ip, p[i].ip);
            break;
        }
    }

    printf("\nCONTATO %d:\n",i);
    printf("nome: %s\n", p[i].nome);
    printf("telefone: %s\n", p[i].telefone);
    printf("ip: %s\n", p[i].ip);

    remote_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (remote_socket == INVALID_SOCKET)
    {
        WSACleanup();
        msg_err_exit("socket() failed\n");
    }

    // preenchendo o remote_address (servidor)
    memset(&remote_address, 0, sizeof(remote_address));
    remote_address.sin_family = AF_INET;
    remote_address.sin_addr.s_addr = inet_addr(remote_ip);
    remote_address.sin_port = htons(remote_port);

    printf("\n\nconectando com %s\n",p[i].nome);
    if (connect(remote_socket, (struct sockaddr *) &remote_address, sizeof(remote_address)) == SOCKET_ERROR)
    {
        WSACleanup();
        msg_err_exit("connect() failed\n");
    }

}

void desconectar_client(){

    printf("encerrando conversa\n");
    WSACleanup();
    closesocket(remote_socket);
    //system("PAUSE");
}


//FUNCOES PARA O SERVIDOR


void escolher_conversa_server(){

    int op;
    do{
        cabecalho_zap();

        printf("\t ENTRAR EM CONVERSA\n\n");
        printf("1-Entrar em conversar com contato\n");
        printf("2-Entrar em conversa com grupo (EM CONSTRUCAO)\n");
        printf("3-Voltar\n\n");

        printf("digite opcao:");
        scanf("%d",&op);


        switch(op){
            case 1:     conversa_contato_server();
                break;
            case 2:     conversa_grupo_server();
                break;
            default:
                break;
        }

        system("cls");
    }while(op!=3);
}

int conversa_contato_server(){

    conectar_server();
    if(sem_conexao==1){
        sem_conexao=0;
        return 0;
    }

    do
    {
        // limpa o buffer
        memset(&message, 0, BUFFER_SIZE);

        // recebe a mensagem do cliente
        message_length = recv(remote_socket, message, BUFFER_SIZE, 0);
        if(message_length == SOCKET_ERROR)
            msg_err_exit("recv() failed\n");

        // exibe a mensagem na tela
        printf("%s: %s\n", inet_ntoa(remote_address.sin_addr), message);


        if(   strcmp(message, EXIT_CALL_STRING) !=0 ){
            printf("digite msg: ");
            // limpa o buffer
            memset(&message, 0, BUFFER_SIZE);
            //fgets(message,255,stdin);
            setbuf(stdin,NULL);
            scanf("%[^\n]s", message);

            // envia a mensagem para o client
            send(remote_socket, message, 115, 0);
        }
    }while(strcmp(message, EXIT_CALL_STRING)); // sai quando receber um "#sair" do cliente

    desconectar_server();

    system("PAUSE");

    return 0;
}

void conversa_grupo_server(){

}

void conectar_server(){

    if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0)
        msg_err_exit("WSAStartup() failed\n");

    // criando o socket local para o servidor
    local_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (local_socket == INVALID_SOCKET)
    {
        WSACleanup();
        msg_err_exit("socket() failed\n");
    }

    printf("Porta local: ");
    scanf("%d", &local_port);
    fflush(stdin);

    // zera a estrutura local_address
    memset(&local_address, 0, sizeof(local_address));

    // internet address family
    local_address.sin_family = AF_INET;

    // porta local
    local_address.sin_port = htons(local_port);

    // endereco
    local_address.sin_addr.s_addr = htonl(INADDR_ANY); // inet_addr("127.0.0.1")

    // interligando o socket com o endereço (local)
    if (bind(local_socket, (struct sockaddr *) &local_address, sizeof(local_address)) == SOCKET_ERROR)
    {
        WSACleanup();
        closesocket(local_socket);
        msg_err_exit("bind() failed\n");
    }

    // coloca o socket para escutar as conexoes
    if (listen(local_socket, BACKLOG_MAX) == SOCKET_ERROR)
    {
        WSACleanup();
        closesocket(local_socket);
        msg_err_exit("listen() failed\n");
    }

    remote_length = sizeof(remote_address);

    printf("aguardando alguma conexao...\n");
    remote_socket = accept(local_socket, (struct sockaddr *) &remote_address, &remote_length);
    if(remote_socket == INVALID_SOCKET)
    {
        WSACleanup();
        closesocket(local_socket);
        msg_err_exit("accept() failed\n");
    }

    printf("conexao estabelecida com %s\n", inet_ntoa(remote_address.sin_addr));
    printf("aguardando mensagens...\n");

}

void desconectar_server(){
    printf("encerrando conversa\n");
    WSACleanup();
    closesocket(local_socket);
    closesocket(remote_socket);
    //system("PAUSE");
}




