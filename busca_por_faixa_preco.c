#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  

// Estrutura utilizada no projeto do grupo. 
typedef struct {
    char nome[100];       
    char categoria[100];  
    float preco;          
} Produto;

// Descarta os caracteres restantes da linha digitada.
void limparEntrada(void) {
    int caractere;
    
    while ((caractere = getchar()) != '\n' && caractere != EOF) {   // getchar lê um caractere por vez. O laço termina na quebra de linha ou no fim da entrada.
        // os caracteres depois do \n sao descartados
    }
}

void buscarPorFaixa(void) { //função void de busca por produto através da faixa de preço
    FILE *arquivo; // ponteiro usado para acessar o arquivo.

    char linha[256]; // armazena uma linha do arquivo por vez.

    float precoMinimo;
    float precoMaximo;

    int encontrado = 0; // aqui eu defino uma variavel para registrar quando se encontra um produto, ocupando o lugar de 0 produtos encontrados (por enquanto)

    printf("\n===== BUSCAR POR FAIXA DE PRECO =====\n");

    printf("Digite o preco minimo: ");

    if (scanf("%f", &precoMinimo) != 1) { //%F lê o float
        limparEntrada(); //função de limpar o console
        printf("Entrada invalida. Digite um numero.\n"); 
        return; // Encerra a função.
    }

    limparEntrada(); // remove a quebra de linha deixado pelo scanf

    printf("Digite o preco maximo: ");

    if (scanf("%f", &precoMaximo) != 1) { 
        limparEntrada();
        printf("Entrada invalida. Digite um numero.\n");
        return;
    }

    limparEntrada();

    // || significa OU.
    // Rejeita a busca se qualquer um dos preços for negativo.
    if (precoMinimo < 0 || precoMaximo < 0) {
        printf("Os precos nao podem ser negativos.\n");
        return;
    }

    if (precoMinimo > precoMaximo) {
        printf("O preco minimo nao pode ser maior que o maximo.\n");
        return;
    }

    // Abre o arquivo no modo "r": somente leitura.
    arquivo = fopen("produtos.csv", "r");

    // NULL indica que o arquivo não pôde ser aberto.
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir produtos.csv.\n");
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

        // Formato esperado: nome;categoria;preco
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
            printf("Preco: R$ %.2f\n", produto.preco);

            encontrado = 1; // Registra que houve um resultado.
        }
    }

    fclose(arquivo); // Fecha o arquivo após a leitura.

    if (encontrado == 0) {
        printf("\nNenhum produto encontrado nessa faixa de preco.\n");
    }
}

// main apenas para testar sua função separadamente.
int main(void) {
    buscarPorFaixa(); // Executa a busca.

    return 0; // Informa que o programa terminou normalmente.
}
