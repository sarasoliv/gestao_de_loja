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
