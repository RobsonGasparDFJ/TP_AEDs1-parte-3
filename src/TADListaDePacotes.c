#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/TADListaDePacotes.h"


/*funcao que esvazia a lista ou inicializa uma lista vazia*/
void fazListaVazia(TListaDePacotes* l){
    l->primeiro = (apontador) malloc(sizeof(celula));
    l->ultimo = l->primeiro;
    l->primeiro->prox = NULL;
}

/*insere no final da lista*/
void insereFinal(TListaDePacotes* l,TPacote x){
    l->ultimo->prox = (apontador) malloc(sizeof(celula));
    l->ultimo = l->ultimo->prox;
    l->ultimo->p = x;
    l->ultimo->prox = NULL;
}

/*remove o item do inicio da lista de pacotes*/
void removeInicio(TListaDePacotes* l,TPacote* pack){
    apontador aux;
    if (l->primeiro == l->ultimo){
        return;
    }

    aux = l->primeiro->prox;
    *pack = aux->p;
    l->primeiro->prox = aux->prox;

    if (aux == l->ultimo){
        l->ultimo = l->primeiro;
    }
    free(aux);
}

/*imprime a lista de pacotes*/
void imprimeLista(TListaDePacotes* l){
    if(l->primeiro == l->ultimo){
        printf("Lista Vazia!");
        return;
    }
    celula* aux;
    aux = l->primeiro->prox;
    while(aux!=NULL){
            printf("\nConteudo: %s\nDestinatario: %s\nPeso: %d\nDistancia: %d",getConteudo(&aux->p),getDestinatario(&aux->p),getPeso(&aux->p),getDistancia(&aux->p));
            printf("\n--------------------------------------------------------------\n");
        aux = aux->prox;
    }
}

int TamanhoDaLista(TListaDePacotes* l){
    celula* aux = l->primeiro->prox;
    int contador = 0;
    while(aux!= NULL){
            contador++;
        aux = aux->prox;
    }
    return contador;
}

celula* PercorrePorIndicie(TListaDePacotes* l,int indicie){
    int i = 0;
    celula* atual = l->primeiro->prox;
    while(atual != NULL && i < indicie) {
            atual = atual->prox;
            i++;
        }
        return atual; // pode retornar NULL se index >= tamanho
    }
