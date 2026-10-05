#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura do produto
typedef struct {
    char nome[100];
    char categoria[100];
    float preco;
} Produto;


// BUSCA POR CATEGORIA
void buscarPorCategoria() {
    FILE *arquivo;
    char linha[200];
    char categoriaBusca[100];
    int encontrado = 0;

    printf("\n===== BUSCAR POR CATEGORIA =====\n");
    printf("Digite a categoria: ");
    scanf(" %99[^\n]", categoriaBusca);

    arquivo = fopen("produtos.csv", "r");

    if (arquivo == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

        Produto produto;
        char *campo;

        // Remove o \n do final da linha
        linha[strcspn(linha, "\r\n")] = '\0';

        // Nome
        campo = strtok(linha, ";");

        if (campo == NULL)
            continue;

        strcpy(produto.nome, campo);


        // Categoria
        campo = strtok(NULL, ";");

        if (campo == NULL)
            continue;

        strcpy(produto.categoria, campo);


        // Preco
        campo = strtok(NULL, ";");

        if (campo == NULL)
            continue;

        produto.preco = atof(campo);


        // Verifica se pertence a categoria procurada
        if (strcmp(produto.categoria, categoriaBusca) == 0) {

            printf("\nProduto encontrado!\n");
            printf("Nome: %s\n", produto.nome);
            printf("Categoria: %s\n", produto.categoria);
            printf("Preco: R$ %.2f\n", produto.preco);

            encontrado = 1;
        }
    }

    fclose(arquivo);

    if (encontrado == 0) {
        printf("\nNenhum produto encontrado nessa categoria.\n");
    }
}
