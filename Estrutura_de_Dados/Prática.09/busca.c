//Estêvão Sousa
//Larissa De Brito
//Davi Roriz

#include <stdio.h>
#include <stdlib.h>

struct arvore {
    int info;
    struct arvore* esquerda;
    struct arvore* direita;
};
typedef struct arvore Arvore;

Arvore* inicializa_Arvore(int num) {
    Arvore* novo = (Arvore*)malloc(sizeof(Arvore));
    novo->info = num;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

Arvore* inserir(Arvore* pai, int num) {
    if (pai == NULL) {
        return inicializa_Arvore(num);
    }
    if (num <= pai->info) {
        pai->esquerda = inserir(pai->esquerda, num);
    } else {
        pai->direita = inserir(pai->direita, num);
    }
    return pai;
}

Arvore* encontrarMinimo(Arvore* pai) {
    if (pai == NULL) {
        return NULL;
    }
    if (pai->esquerda == NULL) {
        return pai;
    }
    return encontrarMinimo(pai->esquerda);
}

Arvore* remover(Arvore* pai, int num) {
    if (pai == NULL) {
        return NULL;
    }
    if (num < pai->info) {
        pai->esquerda = remover(pai->esquerda, num);
    } else if (num > pai->info) {
        pai->direita = remover(pai->direita, num);
    } else {
        if (pai->esquerda == NULL && pai->direita == NULL) {
            free(pai);
            return NULL;
        } else if (pai->esquerda == NULL) {
            Arvore* temp = pai->direita;
            free(pai);
            return temp;
        } else if (pai->direita == NULL) {
            Arvore* temp = pai->esquerda;
            free(pai);
            return temp;
        } else {
            Arvore* minimo = encontrarMinimo(pai->direita);
            pai->info = minimo->info;
            pai->direita = remover(pai->direita, minimo->info);
        }
    }
    return pai;
}

void preordem(Arvore* pai) {
    if (pai != NULL) {
        printf("%d ", pai->info);
        preordem(pai->esquerda);
        preordem(pai->direita);
    }
}

void libera_Arvore(Arvore* pai) {
    if (pai != NULL) {
        libera_Arvore(pai->esquerda);
        libera_Arvore(pai->direita);
        free(pai);
    }
}

int main(void) {
    int N;
    while (scanf("%d", &N) == 1 && N != 0) {
        Arvore* pai = NULL;
        for (int i = 0; i < N; i++) {
            char operacao;
            int num;
            scanf(" %c %d", &operacao, &num);
            if (operacao == 'I') {
                pai = inserir(pai, num);
            } else if (operacao == 'R') {
                pai = remover(pai, num);
            }
            preordem(pai);
            printf("\n");
        }
        //preordem(pai);
        printf("\n\n");
        libera_Arvore(pai);
    }
    return 0;
}