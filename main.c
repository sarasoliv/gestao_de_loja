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

//2
void listar() {
    FILE *arquivo;
    char linha[200];
    char *nome;
    char *categoria;
    char *preco;
    int contador = 1;

    arquivo = fopen("produtos.csv", "r");

    if (arquivo == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\n===== PRODUTOS CADASTRADOS =====\n");

    while (fgets(linha, 200, arquivo) != NULL) {

        nome = strtok(linha, ";\n");
        categoria = strtok(NULL, ";\n");
        preco = strtok(NULL, ";\n");

        if (nome != NULL && categoria != NULL && preco != NULL) {
            printf("\nProduto %d\n", contador);
            printf("Nome: %s\n", nome);
            printf("Categoria: %s\n", categoria);
            printf("Preco: R$ %s\n", preco);

            contador++;
        }
    }

    fclose(arquivo);
}

//3
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

//4
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

//5
//codigo do jao

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

//7
void atualizar() {
    FILE *arquivo;

    char linhas[100][200];
    char linha[200];

    char produtoBusca[100];
    char novoNome[100];
    char novaCategoria[50];
    char novoPreco[30];

    char *nome;

    int quantidade = 0;
    int posicao = -1;
    int i;

    printf("\n===== ATUALIZAR PRODUTO =====\n");

    printf("Digite o nome do produto que deseja atualizar: ");
    fgets(produtoBusca, 100, stdin);

    produtoBusca[0] = strtok(produtoBusca, "\n");

    arquivo = fopen("produtos.csv", "r");

    if (arquivo == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    while (fgets(linha, 200, arquivo) != NULL) {

        strcpy(linhas[quantidade], linha);

        quantidade++;
    }

    fclose(arquivo);

    for (i = 0; i < quantidade; i++) {

        char copia[200];

        strcpy(copia, linhas[i]);

        nome = strtok(copia, ";\n");

        if (nome != NULL) {

            if (strcmp(nome, produtoBusca) == 0) {

                posicao = i;

                break;
            }
        }
    }

    if (posicao == -1) {

        printf("Produto nao encontrado.\n");

        return;
    }

    printf("Novo nome: ");
    fgets(novoNome, 100, stdin);
    strtok(novoNome, "\n");

    printf("Nova categoria: ");
    fgets(novaCategoria, 50, stdin);
    strtok(novaCategoria, "\n");

    printf("Novo preco: ");
    fgets(novoPreco, 30, stdin);
    strtok(novoPreco, "\n");

    arquivo = fopen("produtos.csv", "w");

    if (arquivo == NULL) {

        printf("Erro ao abrir o arquivo.\n");

        return;
    }

    for (i = 0; i < quantidade; i++) {

        if (i == posicao) {

            fprintf(
                arquivo,
                "%s;%s;%s\n",
                novoNome,
                novaCategoria,
                novoPreco
            );

        } else {

            fprintf(arquivo, "%s", linhas[i]);
        }
    }

    fclose(arquivo);

    printf("Produto atualizado com sucesso!\n");
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
