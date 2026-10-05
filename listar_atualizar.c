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
