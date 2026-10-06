#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura para representar o Produto
typedef struct {
    char nome[100];
    char categoria[100];
    float preco;
} Produto;

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
