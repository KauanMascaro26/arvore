#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct no {
    int conteudo;
    struct no *esquerda, *direita;
} No;

typedef struct {
    No *raiz;
} ArvB;


void inserirEsquerda(No *no, int valor) {
    if (no->esquerda == NULL) {
        No *novo = (No *)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        no->esquerda = novo;
    } else {
        if (valor < no->esquerda->conteudo) {
            inserirEsquerda(no->esquerda, valor);
        } else {
            inserirDireita(no->esquerda, valor);
        }
    }
}

void inserirDireita(No *no, int valor) {
    if (no->direita == NULL) {
        No *novo = (No *)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        no->direita = novo;
    } else {
        if (valor > no->direita->conteudo) {
            inserirDireita(no->direita, valor);
        } else {
            inserirEsquerda(no->direita, valor);
        }
    }
}

void inserir(ArvB *arv, int valor) {
    if (arv->raiz == NULL) {
        No *novo = (No *)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        arv->raiz = novo;
    } else {
        if (valor < arv->raiz->conteudo) {
            inserirEsquerda(arv->raiz, valor);
        } else {
            inserirDireita(arv->raiz, valor);
        }
    }
}

No* encontrarMinimo(No *no) {
    while (no->esquerda != NULL) {
        no = no->esquerda;
    }
    return no;
}

No* remover(No *raiz, int valor) {
    if (raiz == NULL) {
        printf("Valor %d não encontrado na árvore.\n", valor);
        return raiz;
    }

    if (valor < raiz->conteudo) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->conteudo) {
        raiz->direita = remover(raiz->direita, valor);
    } else {
        if (raiz->esquerda == NULL) {
            No *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        No *temp = encontrarMinimo(raiz->direita);
        raiz->conteudo = temp->conteudo;
        raiz->direita = remover(raiz->direita, temp->conteudo);
    }
    return raiz;
}

void imprimir(No *raiz) {
    if (raiz != NULL) {
        imprimir(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->direita);
    }
}

int main() {
    setlocale(LC_ALL, "portuguese");

    int opcao, valor;
    ArvB arv;
    arv.raiz = NULL;

    do {
        printf("\n[0] Sair\n[1] Inserir\n[2] Remover\n[3] Imprimir\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                printf("Saindo...\n");
                break;
            case 1:
                printf("\nDigite um valor: ");
                scanf("%d", &valor);
                inserir(&arv, valor);
                break;
            case 2:
                printf("\nDigite o valor a ser removido: ");
                scanf("%d", &valor);
                arv.raiz = remover(arv.raiz, valor);
                break;
            case 3:
                printf("\nImpressão da Árvore Binária: \n");
                imprimir(arv.raiz);
                printf("\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

