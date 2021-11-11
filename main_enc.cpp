#include <iostream>

using namespace std;

struct Produto{
    int peso;
    int valor;
};

struct ItemProduto{
    Produto produto;
    ItemProduto * prox;
};

struct ListaProduto{
    int qtde = 0;
    ItemProduto * item = NULL;
};

const int qtdeProdutos = 7;
const int capacidade = 23;
int matriz[qtdeProdutos+1][capacidade+1];

Produto produtos[qtdeProdutos];
ListaProduto * lProdutos = new ListaProduto;
//Produto produtos[qtdeProdutos] = {{1,1},{2,6},{5,18},{6,22},{7,28},{9,40},{11,60}};


Produto constroiProduto(int valor, int peso){
    Produto p;
    p.peso = peso;
    p.valor = valor;
    return p;
}

ItemProduto * alocaItemProduto(Produto p){
    ItemProduto * item = new ItemProduto;
    item->produto = p;
    item->prox = NULL;
    return item;
}

void addProdutoEmOrdemPorValor(int valor, int peso){

    ItemProduto * item = alocaItemProduto(constroiProduto(valor, peso));

    lProdutos->qtde++;

    if(lProdutos->item==NULL){
        lProdutos->item = item;
    }else{
        ItemProduto * aux = lProdutos->item;
        ItemProduto * ant = aux;
        while(aux!=NULL && aux->produto.valor < item->produto.valor){
            ant = aux;
            aux = aux->prox;
        }
        if(aux==NULL){
            ant->prox = item;
        }else{
            item->prox = aux;

            if(lProdutos->item==aux){
                lProdutos->item=item;
            }else{
                ant->prox = item;
            }
        }
    }
}

void listarProdutos(){
    cout << "\n\n----- LISTAR PRODUTOS -----\n\n";
    cout << "P - V\n";
    ItemProduto * aux = lProdutos->item;
    while(aux!=NULL){
        cout << aux->produto.peso << " - " << aux->produto.valor << endl;
        aux = aux->prox;
    }
}

void menu(){
    cout << "\n\n----- MENU -----\n";
    cout << "1 - Cadastrar produto;\n"
        << "2 - Listar produtos;\n"
        << "3 - Calcular;\n"
        << "0 - SAIR;\n";
}

void calcular(){
    for(int p=0; p<=lProdutos->qtde; p++){
        for(int c=0; c<=capacidade; c++){
            if(p==0 || c==0){
                matriz[p][c] = 0;
            }else if(produtos[p-1].peso<=c){
                matriz[p][c] = produtos[p-1].valor + matriz[p-1][c-produtos[p-1].peso];
            }else{
                matriz[p][c] = matriz[p-1][c];
            }
        }
    }
}


int main(){

    int opcao, peso, valor;
    int qtde = 0;

    cout << "CAPACIDADE DA MOCHILA: " << capacidade;
    cout << "QUANTIDADE DE PRODUTOS: " << qtdeProdutos;

    do{
        menu();
        cout << "Digite a opcao: ";
        cin >> opcao;

        switch(opcao){
            case 1:
                cout << "\n----- CADASTRAR PRODUTO -----\n";
                if(lProdutos->qtde<qtdeProdutos){
                    for(int i=0; i<qtdeProdutos; i++){
                        cout << "Digite o peso do produto " << i << ": ";
                        cin >> peso;
                        cout << "Digite o valor do produto " << i << ": ";
                        cin >> valor;
                        addProdutoEmOrdemPorValor(valor, peso);
                    }
                }
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                calcular();
                for(int p=0; p<=qtdeProdutos; p++){
                    for(int c=0; c<=capacidade; c++){
                        cout << matriz[p][c] << " ";
                    }
                    cout << endl;
                }
                cout << matriz[7][23];
                break;

        }

    }while(opcao!=0);

    return 0;
}
