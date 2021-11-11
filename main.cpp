#include <iostream>

using namespace std;

//definicao da quantidade de produtos
const int qtdeProdutos = 7;

//definicao da capacidade da mochila
const int capacidade = 23;

//estrutura para memorizar os calculos
int matriz[qtdeProdutos+1][capacidade+1];

//modelo do produto
struct Produto{
    int peso;
    int valor;
    bool incluido = false;
};

//lista de produtos
Produto produtos[qtdeProdutos];

//Produto produtos[qtdeProdutos] = {{1,1},{2,6},{5,18},{6,22},{7,28},{9,40},{11,60}};

//adiciona um produto na lista de forma ordenada pelo valor
int addProdutoEmOrdemPorValor(int valor, int peso, int qtde, int qtdeProdutos){
    if(qtde<qtdeProdutos){
        Produto p;
        p.peso = peso;
        p.valor = valor;
        if(qtde==0){
            produtos[qtde] = p;
        }else{
            int i;
            for(i=0; i<qtde; i++){
                if(produtos[i].valor>p.valor){
                    for(int j=qtde; j>i; j--){
                        produtos[j] = produtos[j-1];
                    }
                    break;
                }
            }
            produtos[i] = p;
        }
        qtde++;
    }
    return qtde;
}

//adiciona um produto na lista
int addProduto(int valor, int peso, int qtde, int qtdeProdutos){
    if(qtde<qtdeProdutos){
        Produto p;
        p.peso = peso;
        p.valor = valor;
        produtos[qtde] = p;
        qtde++;
    }
    return qtde;
}

//lista os produtos cadastrados
void listarProdutos(int qtde){
    cout << "\n\n----- LISTAR PRODUTOS -----\n";
    cout << "P - V\n";
    for(int i=0; i<qtde; i++){
        cout << produtos[i].peso << " - " << produtos[i].valor << endl;
    }
}

//imprime as opcoes do menu
void menu(){
    cout << "\n\n----- MENU -----\n";
    cout << "1 - Cadastrar produto;\n"
        << "2 - Listar produtos;\n"
        << "3 - Calcular;\n"
        << "4 - Zerar Produtos;\n"
        << "0 - SAIR;\n";
}

//preenche a matriz de memoria de calculo
void calcular(int qtdeProdutosCadastrados){
    //pecorre os produtos cadastrados
    for(int p=0; p<=qtdeProdutosCadastrados; p++){
        //pecorre as possiveis capacidades da mochila
        for(int c=0; c<=capacidade; c++){
            //preenche com 0 qdo de produto 0 ou capacidade 0
            if(p==0 || c==0){
                matriz[p][c] = 0;
            //caso o produto da vez caiba na capacidade da vez
            }else if(produtos[p-1].peso<=c){
                //                  valor da vez     + valor que ainda cabe do estagio anterior
                int valorDaVez = produtos[p-1].valor + matriz[p-1][c-produtos[p-1].peso];
                //  valor com a capacidade maxima do estagio anterior
                int valorMaxAnterior = matriz[p-1][c];
                // memoriza o maximo
                matriz[p][c] = valorDaVez>valorMaxAnterior?valorDaVez:valorMaxAnterior; //poderia evitar essa comparacao se o vetor de produtos fosse ordenado pelo valor
            //se nao couber, usar valor ja calculado no estagio anterior
            }else{
                matriz[p][c] = matriz[p-1][c];
            }
        }
    }
}

int calcularQtdeDigitos(int n){
    int nDigitos = 0;
    do {
        ++nDigitos;
        n /= 10;
    } while (n);
    return nDigitos;
}

void formataNumero(int numero, int maxQtdeDigitos){
    int nDigitosAtual = calcularQtdeDigitos(numero);
    for(int i=0; i<maxQtdeDigitos-nDigitosAtual; i++){
        cout << 0;
    }
    cout << numero;
}

int main(){

    int opcao, peso, valor;
    int qtde = 0;
    cout << "\n----- MOCHILA BINARIA -----";
    cout << "\nCAPACIDADE DA MOCHILA: " << capacidade;
    cout << "\nQUANTIDADE DE PRODUTOS: " << qtdeProdutos;
    cout << endl;

    do{
        menu();
        cout << "Digite a opcao: ";
        cin >> opcao;

        switch(opcao){
            case 1:
                cout << "\n----- CADASTRAR PRODUTO -----\n";
                cout << "Digite o peso: ";
                cin >> peso;
                cout << "Digite o valor: ";
                cin >> valor;
                qtde = addProduto(valor, peso, qtde, qtdeProdutos);
                break;
            case 2:
                listarProdutos(qtde);
                break;
            case 3:
                //if(qtde==qtdeProdutos){
                {

                    calcular(qtde);
                    int qtdeMaxDigitos = calcularQtdeDigitos(matriz[qtde][capacidade]);

                    cout << "\n\n----- MEMORIA DE CALCULO -----\n\n";
                    for(int p=0; p<=qtde; p++){
                        for(int c=0; c<=capacidade; c++){
                            formataNumero(matriz[p][c], qtdeMaxDigitos);
                            cout <<  " ";
                        }
                        cout << endl;
                    }

                    int p = qtde;
                    int c = capacidade;
                    for(int i=0; i<qtde; i++){
                        while(p>0&&c>0){
                            if(matriz[p][c]!=matriz[p-1][c]){
                                produtos[p-1].incluido = true;
                                c = c-produtos[p-1].peso;
                            }
                            p--;
                        }
                    }

                    cout << "\n\n----- PRODUTOS INCLUIDOS-----\n";
                    cout << "P - V\n";
                    for(int i=0; i<qtde; i++){
                        if(produtos[i].incluido){
                            cout << produtos[i].peso << " - " << produtos[i].valor << endl;
                        }
                    }
                    cout << "\nVALOR MAXIMO: " << matriz[qtde][capacidade];

               // }else{
                 //   cout << "\nMENSAGEM: ainda nao atingiu a quantidade de produtos.\n"
                 //       << "falta cadastrar: " << qtdeProdutos-qtde << " produtos.";
                }
                break;
            case 4:
                qtde = 0;
            default:
                cout << "\nMENSAGEM: opcao invalida;";
        }

    }while(opcao!=0);

    return 0;
}
