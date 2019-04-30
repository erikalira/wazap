#include <stdio.h>

int main ()
{
	char arquivo_usuario[40];
	FILE *criar_banco;
	char username[20];

	printf("Usuario: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]s", username);

	sprintf( arquivo_usuario, "dados/contatos_%s.txt", username);

    //cria o arquivo para salvar os contatos do usuario
    criar_banco = fopen(arquivo_usuario, "w");

    //salva um primeiro contato teste para padronizar
    fprintf(criar_banco, "nome telefone ip\n");

    fclose(criar_banco);

	return 0;
}
