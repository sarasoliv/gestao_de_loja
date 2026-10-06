#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//funções
// Estrutura para representar o Produto
typedef struct {
    char nome[100];
    char categoria[100];
    float preco;
} Produto;

void limparEntrada(void) {
    int caractere;
    
    while ((caractere = getchar()) != '\n' && caractere != EOF) {   // getchar lê um caractere por vez. O laço termina na quebra de linha ou no fim da entrada.
        // os caracteres depois do \n sao descartados
    }
}

//1
// Função para cadastrar um produto no arquivo produtos.csv
void cadastrarProduto() {
    FILE *arquivo;
    Produto produto;

    printf("\n===== CADASTRAR PRODUTO =====\n");

    printf("Digite o nome do produto: ");
    if (scanf(" %99[^\n]", produto.nome) != 1) {
        printf("Entrada inválida.\n");
        return;
    }

    printf("Digite a categoria do produto: ");
    if (scanf(" %99[^\n]", produto.categoria) != 1) {
        printf("Entrada inválida.\n");
        return;
    }

    printf("Digite o preço do produto: ");
    if (scanf("%f", &produto.preco) != 1) {
        printf("Entrada inválida.\n");
        return;
    }

    // Abre o arquivo no modo "a" (append) para adicionar o novo registro ao final
    arquivo = fopen("produtos.csv", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para gravação.\n");
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
            printf("Preço: R$ %s\n", preco);

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
        printf("Entrada inválida.\n");
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
            printf("Preço: R$ %.2f\n", produto.preco);
            encontrado = 1;
            break;
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("\nProduto não encontrado.\n");
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


        // Preço
        campo = strtok(NULL, ";");

        if (campo == NULL)
            continue;

        produto.preco = atof(campo);


        // Verifica se pertence a categoria procurada
        if (strcmp(produto.categoria, categoriaBusca) == 0) {

            printf("\nProduto encontrado!\n");
            printf("Nome: %s\n", produto.nome);
            printf("Categoria: %s\n", produto.categoria);
            printf("Preço: R$ %.2f\n", produto.preco);

            encontrado = 1;
        }
    }

    fclose(arquivo);

    if (encontrado == 0) {
        printf("\nNenhum produto encontrado nessa categoria.\n");
    }
}

//5
void buscarPorFaixa(void) { //função void de busca por produto através da faixa de preço
    FILE *arquivo; // ponteiro usado para acessar o arquivo.

    char linha[256]; // armazena uma linha do arquivo por vez.

    float precoMinimo;
    float precoMaximo;

    int encontrado = 0; // aqui eu defino uma variável para registrar quando se encontra um produto, ocupando o lugar de 0 produtos encontrados (por enquanto)

    printf("\n===== BUSCAR POR FAIXA DE PRECO =====\n");

    printf("Digite o preço mínimo: ");

    if (scanf("%f", &precoMinimo) != 1) { //%F lê o float
        limparEntrada(); //função de limpar o console
        printf("Entrada inválida. Digite um número.\n"); 
        return; // Encerra a função.
    }

    limparEntrada(); // remove a quebra de linha deixada pelo scanf

    printf("Digite o preço máximo: ");

    if (scanf("%f", &precoMaximo) != 1) { 
        limparEntrada();
        printf("Entrada inválida. Digite um número.\n");
        return;
    }

    limparEntrada();

    // || significa OU.
    // Rejeita a busca se qualquer um dos preços for negativo.
    if (precoMinimo < 0 || precoMaximo < 0) {
        printf("Os preços não podem ser negativos.\n");
        return;
    }

    if (precoMinimo > precoMaximo) {
        printf("O preço mínimo não pode ser maior que o maximo.\n");
        return;
    }

    // Abre o arquivo no modo "r": somente leitura.
    arquivo = fopen("produtos.csv", "r");

    // NULL indica que o arquivo não pôde ser aberto.
    if (arquivo == NULL) {
        printf("Não foi possível abrir produtos.csv.\n");
        return;
    }

    // %.2f exibe um número com duas casas decimais.
    printf("\nProdutos entre R$ %.2f e R$ %.2f:\n",
           precoMinimo, precoMaximo);

    // fgets lê uma linha por vez.
    // sizeof(linha) informa o tamanho do espaço disponível.
    // O laço continua enquanto a leitura retornar algo diferente de NULL.
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        Produto produto; // Guarda os dados do produto desta linha.
        char *campo;     // Aponta para cada campo separado por strtok.

        // Localiza a primeira quebra de linha e substitui por '\0'.
        // '\0' indica o fim de uma string em C.
        linha[strcspn(linha, "\r\n")] = '\0';

        // Formato esperado: nome;categoria;preço
        // A primeira chamada separa o nome.
        campo = strtok(linha, ";");

        if (campo == NULL) {
            continue; // Ignora a linha se o campo não existir.
        }

        // Copia o nome respeitando o tamanho do destino.
        snprintf(produto.nome, sizeof(produto.nome), "%s", campo);

        // NULL faz strtok continuar separando a mesma linha.
        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        snprintf(produto.categoria,
                 sizeof(produto.categoria),
                 "%s",
                 campo);

        // Obtém o terceiro campo: o preço.
        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        // Converte, por exemplo, o texto "89.90" em um número.
        // O arquivo deve conter preços válidos, com ponto decimal.
        produto.preco = atof(campo);

        // && significa E: as duas condições devem ser verdadeiras.
        // >= e <= incluem os limites informados na busca.
        if (produto.preco >= precoMinimo &&
            produto.preco <= precoMaximo) {
            printf("\nProduto encontrado!\n");
            printf("Nome: %s\n", produto.nome);
            printf("Categoria: %s\n", produto.categoria);
            printf("Preço: R$ %.2f\n", produto.preco);

            encontrado = 1; // Registra que houve um resultado.
        }
    }

    fclose(arquivo); // Fecha o arquivo após a leitura.

    if (encontrado == 0) {
        printf("\nNenhum produto encontrado nessa faixa de preço.\n");
    }
}

//6
void remover(void){
		//remove todas as infos do produto
		// 1. Remove do ARRAY
		char produto_removido[100];

    printf("\n===== REMOVER PRODUTO =====\n");
    printf("Digite o nome do produto que deseja remover: ");

    if (scanf(" %99[^\n]", produto_removido) != 1) {
        printf("Entrada inválida.\n");
        limparEntrada();
        return;
    }

    limparEntrada();
    printf("\nProduto informado para remoção: %s\n", produto_removido);
    printf("-------------------------------------");
    
  
    // 2. Abrindo o arquivo original do estoque de produtos em CSV
    FILE *arquivo = fopen("produtos.csv", "r");
        if (arquivo == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo CSV!\n\n");
        return;
    }
    printf("\n\narquivo CSV aberto com sucesso!\n");
    printf("-------------------------------------");
    
    // 3. Criando arquivo temporário do estoque de produtos em CSV
    printf("\n\nCriando o arquivo temporário.csv...\n\n");
    FILE *temporario = fopen("temporario.csv", "w");
    if (temporario == NULL) {
        printf("ERRO: Não foi possível criar o arquivo temporário!\n\n");
        fclose(arquivo);
        return;
    }
    printf("Arquivo temporário.csv criado com sucesso!\n\n");
    printf("-------------------------------------");

    // 4. Copia para o temporário tudo,
    //menos o produto removido
    
    printf("\n\nLendo os produtos do arquivo anterior CSV...\n\n");
    printf("O Produto que será apagado é: %s\n\n", produto_removido);

    char linha[256];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char copia[256];
        char *nome;

        snprintf(copia, sizeof(copia), "%s", linha);
        nome = strtok(copia, ";\r\n");

        if (nome == NULL || strcmp(nome, produto_removido) != 0) {
            fprintf(temporario, "%s", linha);

            if (nome != NULL) {
                printf("Copiando: %s\n\n", nome);
            }
        }
        else {
            encontrado = 1;
            printf("NÁO copiando: %s (produto removido)\n", nome);
        }
    }

    printf("Produtos copiados para o arquivo temporário!\n");
		printf("-------------------------------------");

    // 5. Fecha os arquivos    
    printf("\n\nFechando os arquivos...\n\n");
    fclose(arquivo);
    fclose(temporario);
    printf("Arquivos fechados!\n\n");
		printf("-------------------------------------");

    if (encontrado == 0) {
        remove("temporario.csv");
        printf("\n\nProduto não encontrado. Nenhuma alteração foi realizada.\n");
        return;
    }

    // 6. Apaga o CSV antigo
    printf("\n\nApagando o arquivo produtos.csv atual...\n\n");
    if (remove("produtos.csv") != 0) {
        printf("ERRO: Não foi possível apagar o arquivo CSV antigo!\n");
        remove("temporario.csv");
        return;
    }
    printf("arquivo CSV antigo foi apagado!\n\n");
		printf("-------------------------------------");

    // 7. Renomeia o temporário para produtos_estoque.csv
		printf("\n\nRenomeando temporário.csv para produtos.csv...\n\n");
    if (rename("temporario.csv", "produtos.csv") != 0) { //rename(recebe nome, passa nome)
        printf("ERRO: Não foi possível renomear o arquivo temporário!\n");
        return;
    }
    printf("Novo arquivo produtos.csv criado e atualizado com sucesso!\n\n");
    printf("-------------------------------------");
    printf("\nProduto removido com sucesso!\n\n");
}

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

    produtoBusca[strcspn(produtoBusca, "\r\n")] = '\0';

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

        printf("Produto não encontrado.\n");

        return;
    }

    printf("Novo nome: ");
    fgets(novoNome, 100, stdin);
    strtok(novoNome, "\n");

    printf("Nova categoria: ");
    fgets(novaCategoria, 50, stdin);
    strtok(novaCategoria, "\n");

    printf("Novo preço: ");
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
		printf("[5] - Buscar por preço\n");
		printf("[6] - Buscar por categoria\n");
		printf("[7] - Buscar por nome\n");
        printf("[0] - Sair do programa\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida!\n");
            limparEntrada();
            continue;
        }

        limparEntrada();

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                listar();
                break;
            case 3:
                remover();
                break;
            case 4:
                atualizar();
                break;
	        case 5:
                buscarPorFaixa();
                break;
			case 6:
                buscarPorCategoria();
                break;
			case 7:
                buscarPorNome();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
