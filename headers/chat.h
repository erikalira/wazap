#ifndef CHAT_H_INCLUDED
#define CHAT_H_INCLUDED

//FUNCOES PARA O SERVIDOR

void escolher_conversa_client();

int conversa_contato_client();

int conversa_grupo_client();

void conectar_client();

void desconectar_client();


//FUNCOES PARA O SERVIDOR

void escolher_conversa_server();

int conversa_contato_server();

int conversa_grupo_server();

void conectar_server();

void desconectar_server();

#endif // CHAT_H_INCLUDED
