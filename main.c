#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//funcoes
// Estrutura para representar o Produto
typedef struct {
    char nome[100];
    char categoria[100];
    float preco;
} Produto;

//1
// Função para cadastrar um produto no arquivo produtos.csv
void cadastrarProduto() {
    FILE *arquivo;
    Produto produto;

    printf("\n===== CADASTRAR PRODUTO =====\n");

    printf("Digite o nome do produto: ");
    if (scanf(" %99[^\n]", produto.nome) != 1) {
        printf("Entrada invalida.\n");
        return;
    }

    printf("Digite a categoria do produto: ");
    if (scanf(" %99[^\n]", produto.categoria) != 1) {
        printf("Entrada invalida.\n");
        return;
    }

    printf("Digite o preco do produto: ");
    if (scanf("%f", &produto.preco) != 1) {
        printf("Entrada invalida.\n");
        return;
    }

    // Abre o arquivo no modo "a" (append) para adicionar o novo registro ao final
    arquivo = fopen("produtos.csv", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para gravacao.\n");
        return;
    }

    // Escreve os dados formatados com ';' no arquivo
    fprintf(arquivo, "%s;%s;%.2f\n", produto.nome, produto.categoria, produto.preco);

    fclose(arquivo);

    printf("\nProduto cadastrado com sucesso!\n");
}


//6
void remover(int posicao){
	//remove todas as infos do produto
	// 1. Remove do ARRAY
	int i;
	char produto_removido[50];
    strcpy(produto_removido, produtos[posicao].nome);
    
	for (i = posicao; i < tamanho_lista -1; i++){
    	produtos[i] = produtos[i + 1];
    }
    tamanho_lista--;
    printf("\nProduto removido com sucesso!\n\n");
	printf("-------------------------------------");
    
  
    // 2. Abrindo o arquivo original do estoque de produtos em CSV
    FILE *arquivo = fopen("produtos_estoque.csv", "r");
        if (arquivo == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo CSV!\n\n");
        return;
    }
    printf("\n\narquivo CSV aberto com sucesso!\n");
    printf("-------------------------------------");
    
    // 3. Criando arquivo temporário do estoque de produtos em CSV
    printf("\n\nCriando o arquivo temporario.csv...\n\n");
    FILE *temporario = fopen("temporario.csv", "w");
    if (temporario == NULL) {
        printf("ERRO: Não foi possível criar o arquivo temporário!\n\n");
        fclose(arquivo);
        return;
    }
    printf("Arquivo temporario.csv criado com sucesso!\n\n");
    printf("-------------------------------------");

    // 4. Copia para o temporário tudo,
    //menos o produto removido
    
    printf("\n\nLendo os produtos do arquivo anterior CSV...\n\n");
    printf("O Produto que será apagado é: %s\n\n", produto_removido);

    char linha[100];
    char nome[50];
    float preco;
    int estoque;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "%49[^;];%f;%i", nome, &preco, &estoque);
        if (strcmp(nome, produto_removido) != 0) {
            fprintf(
                temporario,
                "%s;%.2f;%i",
                nome,
                preco,
                estoque
            );
            printf("Copiando: %s\n\n", nome);
        }
        else {
            printf("NÃO copiando: %s (produto removido)\n", nome);
        }
    }

    printf("Produtos copiados para o arquivo temporario!\n");
	printf("-------------------------------------");

    // 5. Fecha os arquivos    
    printf("\n\nFechando os arquivos...\n\n");
    fclose(arquivo);
    fclose(temporario);
    printf("Arquivos fechados!\n\n");
	printf("-------------------------------------");

    // 6. Apaga o CSV antigo
    printf("\n\nApagando o arquivo produtos_estoque.csv atual...\n\n");
    remove("produtos_estoque.csv");
    printf("arquivo CSV antigo foi apagado!\n\n");
	printf("-------------------------------------");

    // 7. Renomeia o temporário para produtos_estoque.csv
	printf("\n\nRenomeando temporario.csv para produtos_estoque.csv...\n\n");
    rename("temporario.csv", "produtos_estoque.csv"); //rename(recebe nome, passa nome)
    printf("Novo arquivo produtos_estoque.csv criado e atualizado com sucesso!\n\n");
    printf("-------------------------------------");
};


int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;

do {
        printf("\n===== Menu de Opções =====\n");
        printf("[1] - Cadastrar produto\n");
        printf("[2] - Listar produtos\n");
        printf("[3] - Remover produto\n");
        printf("[4] - Atualizar produto\n");
        printf("[5] - Sair do programa\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida!\n");
            break;
        }

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                printf("Listar produtos\n");
                break;
            case 3:
                printf("Remover produto\n");
				remover(i);
                break;
            case 4:
                printf("Atualizar produto\n");
                break;
            case 5:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

