//Estêvão Sousa
//Davi Roriz
//Larissa de Brito

#include <iostream>

using namespace std;

// prototipos
class Arvore
{
public:
    int info;
    Arvore *left, *right;

    Arvore(int in){// contrutor para inserir informação
    
        info = in;
        left = right = nullptr;
    };
    // imprime em pré ordem Raiz-Esq-Dir
    void ImprimePreOrdem(){

        cout << info << " ";
        if(left)
            left->ImprimePreOrdem();
        if(right)
            right->ImprimePreOrdem();
    }

    int altura()
    { //raiz nunca é nulo(o proprio nó chama o método), então testa os filhos.
        int alt = 0, he = 0, hd = 0;
        //pega a difereça das alturas
        if (left != nullptr)
            he = left->altura() + 1;
        if (right != nullptr)
            hd = right->altura() + 1;
        //ternaŕio
        alt = (he < hd) ? hd : he;

        return alt; // retorna o maior valor
    }

    bool ehBalanceada() // verifica se está balanceada
    {
        int altE = -1, altD = -1;
        bool balanceada = true;// por algum motivo sempre true

        if (left)// se for null não testa balanceamento
        {
            altE = left->altura(); // pega a altura do filho esquedo
            if (!left->ehBalanceada())//verifica se é balanceado recursivamente
                balanceada = false;// se não é balanceado  retorna falso
        }
        if (right)// o mesmo pro filho direito
        {
            altD = right->altura();
            if (!right->ehBalanceada())
                balanceada = false;
        }

        if (abs(altE - altD) > 1)   // noo fim é testado se o valor absoluto na subtração
            balanceada = false;     // do filho esquedo com o direito é > 1

        return balanceada;
    }

    int FatorBalanceamento()// diferença entre o nó esquerdo e direito
    {   
        int AlturaDir = -1, AlturaEsq = -1;

        if(left){
            AlturaEsq = left->altura();
        }
        if(right){
            AlturaDir = right->altura();
        }
        return (AlturaEsq - AlturaDir);
    }

    void insere(int val){// insere uma arvore binária normalmente
        if(val<=info){
            if(left) {
                left->insere(val);
            } else {
                Arvore* novo = new Arvore(val);
                left = novo;
            }
        }else{
            if(right) {
                right->insere(val);
            } else {
                Arvore* novo = new Arvore(val);
                right = novo;
            }
        }
    }
};

Arvore *RotaDireita(Arvore *A)// ROtação para a direita
{
    //Para rotacioinar para a direita
    //é necessário slavar o endereço do filho
    //esquerdo, aponta-lo para o filho direito
    //filho direito agora é a raiz da sub-arvore
    Arvore *x = A->left;

    A->left = x->right;
    x->right = A;

    return x;
}
Arvore *RotaEsquerda(Arvore *A)
{

    Arvore *x = A->right;
    A->right = x->left;
    x->left = A;

    return x;
}
Arvore *RotaDE(Arvore *A)
{
    A->right = RotaDireita(A->right);
    return RotaEsquerda(A);
}
Arvore *RotaED(Arvore *A)
{
    A->left = RotaEsquerda(A->left);
    return RotaDireita(A);
}

Arvore *Balancear(Arvore **A)
{
    //faz balanceamento enquanto a arvore estiver desbalanceada
    while (!(*A)->ehBalanceada())
    {  
        if((*A)->left)//verifica se o filho esquerdo é folha
            Balancear(&(*A)->left);//balanceia filho esquerdo recursivamente
        if((*A)->right)
            Balancear(&(*A)->right);//balanceia filho esquerdo recursivamente

        int Fator = (*A)->FatorBalanceamento();//atribui valor de fator de balanceamento
        if (Fator > 1)// se o fator for maior q > 1 e menor que -1 está desbalanceado
        {
            if ((*A)->left->FatorBalanceamento() < 0) //se o fator do filho esquerdo for menor que zero
            {
                (*A) = RotaED((*A)); //balanceia esquerda direita
            }
            else
                (*A) = RotaDireita((*A)); // rotaciona para a direita
        }
        if (Fator < -1)
        {
            if ((*A)->right->FatorBalanceamento() > 0)
            {
                (*A) = RotaDE((*A));
            }
            else
                (*A) = RotaEsquerda((*A));
        }
    }
    return (*A);
}

int main()
{

    int Entrada, N;
    Arvore *Tree;

    while (cin >> N && N > 0)
    {
        cin >> Entrada;
        Tree = new Arvore(Entrada);
        for (int i = N-1; i > 0; i--)
        {
            cin >> Entrada;
            Tree->insere(Entrada);
            Tree = Balancear(&Tree);
            
        }
        Tree->ImprimePreOrdem();
    }
}