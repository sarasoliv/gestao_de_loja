void buscarPorNome() {
    FILE *arquivo;
    char linha[200];
    char nomeBusca[100];
    int encontrado = 0;

    printf("\n===== BUSCAR POR NOME =====\n");
    printf("Digite o nome do produto: ");
    if (scanf(" %99[^\n]", nomeBusca) != 1) {
        printf("Entrada invalida.\n");
        return;
    }

    arquivo = fopen("produtos.csv", "r");
    if (arquivo == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        Produto produto;
        char *campo;

        linha[strcspn(linha, "\r\n")] = '\0';

        campo = strtok(linha, ";");
        if (campo == NULL) continue;
        snprintf(produto.nome, sizeof(produto.nome), "%s", campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        snprintf(produto.categoria, sizeof(produto.categoria), "%s", campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        produto.preco = atof(campo);

        if (strcmp(produto.nome, nomeBusca) == 0) { 
            printf("\nProduto encontrado!\n");
            printf("Nome: %s\n", produto.nome);
            printf("Categoria: %s\n", produto.categoria);
            printf("Preco: R$ %.2f\n", produto.preco);
            encontrado = 1;
            break;
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("\nProduto nao encontrado.\n");
    }
}

#include <stdio.h>
#include <locale.h>
int main(){
	
setlocale(LC_ALL, "Portuguese");
int opcao;
	
	printf("===== menu de Opções =====\n");
	printf("[1] - Cadastar produto \n");
	printf("[2] - Listar pr odutos \n");
	printf("[3] - Remover produto \n");
	printf("[4] - Atualizar produto \n");
	printf("[5] - Sair \n ");
	scanf("%d", &opcao);
	
	void cadastrar_usuario(void){
		if "1":
			
	}
	
	switch (opcao) {
		case 7:
			printf("a\n");
		case 1: 
			cadastrar_usuario();
		case 2:
			printf("b\n");
			break;
		case 3:
			printf("c\n");
			break;
		case 4:
			printf("d\n");
			break;
		case 5:
			printf("Saindo do Programa\n");
			break;
		default:
			printf("Selecione uma das opções acima\n");
	}
	
	
	
	return 0;
}
