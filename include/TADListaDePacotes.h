#ifndef LISTA_DE_PACOTES_H
#define LISTA_DE_PACOTES_H

#include "TADPacote.h"

typedef struct celula* apontador;
/*definicao do TAD listadepacotes com implementacao (primeiro a celula)*/

typedef struct celula {
    /*dentro da celula tem um pacote*/
    TPacote p;
    apontador prox;
}celula;

/*de fato, a lista de pacotes*/
typedef struct{
    apontador primeiro,ultimo;
}TListaDePacotes;


/*inicializa uma lista vazia*/
void fazListaVazia(TListaDePacotes* l);

/*insere pacote no final*/
void insereFinal(TListaDePacotes* l,TPacote x);

/*remove pacote no inicio*/
void removeInicio(TListaDePacotes* l,TPacote* pack);

/*imprime os pacotes da lista*/
void imprimeLista(TListaDePacotes* l);
#endif
