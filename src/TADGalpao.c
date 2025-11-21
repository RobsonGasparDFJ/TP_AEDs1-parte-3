#include "../include/TADGalpao.h"

//variaveis de medição de contagem
long long QKcomparacoes = 0;
long long QKmovimentacoes = 10;

TPacote PacoteTransportado;

void InicializarGalpao(TGalpao *Galpao){
    fazListaVazia(&(Galpao->ListaDePacotes));
    // printf("\n O Galpao foi inicializado. \n");
}

void RecebimentoDePacote(TGalpao *Galpao, TPacote pacote){
    insereFinal(&(Galpao->ListaDePacotes), pacote);
}

void EntregaDoDia(TGalpao *Galpao){
    imprimeLista(&(Galpao->ListaDePacotes));
}

void CarregamentoDePacotes(TGalpao *Galpao){
    removeInicio (&(Galpao->ListaDePacotes), &PacoteTransportado);
    // printf("\nPacote retirado para transporte! \n");
}

celula* particao(celula* cabeca, celula* ultima){
    celula* pivo = cabeca;
    celula* anterior = cabeca;
    celula* atual = cabeca;

    while (atual != ultima->prox) {

        QKcomparacoes++;

        if (atual->p.prioridade > pivo->p.prioridade) {
            QKmovimentacoes++;
            int temp = atual->p.prioridade;
            atual->p.prioridade = anterior->prox->p.prioridade;
            anterior->prox->p.prioridade = temp;

            anterior = anterior->prox;
        }

        atual = atual->prox;
    }

    int temp = pivo->p.prioridade;
    pivo->p.prioridade = anterior->p.prioridade;
    anterior->p.prioridade = temp;

    return anterior;
}

void AjudanteQuicksort(celula* cabeca, celula* ultima){

    if (cabeca == NULL || cabeca == ultima)
        return;

    celula* pivo = particao(cabeca, ultima);

    AjudanteQuicksort(cabeca, pivo);
    AjudanteQuicksort(pivo->prox, ultima);
}

celula* quickSort(TGalpao* galpao){

    celula* cabeca = galpao->ListaDePacotes.primeiro;
    celula* ultimo = galpao->ListaDePacotes.ultimo;

    AjudanteQuicksort(cabeca, ultimo);

    return cabeca;
}

void SelectionSort(TGalpao *Galpao, int* comparacoes,int* movimentacoes){
    for (celula *i = Galpao->ListaDePacotes.primeiro->prox; i != NULL; i = i->prox){
        celula *maior = i;
        for (celula *j = i->prox; j != NULL; j = j->prox){
            *comparacoes = *comparacoes+1;
            if (j->p.prioridade > maior->p.prioridade){
                maior = j;
            }
        }
        if (maior != i) {
            TPacote tmp = i->p;
            i->p = maior->p;
            maior->p = tmp;
            (*movimentacoes)++;
        }
    }
}
