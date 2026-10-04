#include<stdio.h>


//funcoes

//6
tamanho_lista = //numero de produtos;
	
void remover(int posicao){
	//remove todas as infos do produto
	int i;
	    for (i = posicao; i < tamanho_lista; i++) {
        produtos[i] = produtos[i + 1];
    }
    printf("\nProduto removido com sucesso!\n");	
};

int main(){
  remover(i);
  return 0;
};
