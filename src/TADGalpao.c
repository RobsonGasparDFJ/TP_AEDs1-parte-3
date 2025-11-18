#include "../include/TADGalpao.h"
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

void Shellsort(TGalpao *Galpao,int *comparacoes, int *movimentacoes){
    int h = 1;
    int tamanho = TamanhoDaLista(&(Galpao->ListaDePacotes));
    // Gera o maior h possível da sequência de Knuth
    while (h < tamanho/3) {
        h = 3*h + 1;
    }
    while (h >= 1) {
        for(int i = h; i < tamanho; i++){
            //pegar o nó atual (no índice i)
            celula* indicieI = PercorrePorIndicie(&(Galpao->ListaDePacotes), i);
            TPacote aux = indicieI->p;
            (*movimentacoes)++;
            //preparar para comparar com posições anteriores
            int j = i;
            celula* indicieJmH = PercorrePorIndicie(&(Galpao->ListaDePacotes), j-h);
            (*comparacoes)++;
            while(j >= h && aux.prioridade < indicieJmH->p.prioridade){
                    //mover o nó j-h para a posição j
               celula* IndicieJ = PercorrePorIndicie(&(Galpao->ListaDePacotes), j);
               (*movimentacoes)++;
               IndicieJ->p = indicieJmH->p;
               j -= h;
               //atualizar o nó j-h para continuar o loop (se j ainda não passou do limite)
               if(j >= h){
                   indicieJmH = PercorrePorIndicie(&(Galpao->ListaDePacotes), j-h);
                   (*comparacoes)++;
               }
               //Elemento aux na posição correta
               celula* TrocaFinal = PercorrePorIndicie(&(Galpao->ListaDePacotes), j);
               TrocaFinal->p = aux;
               (*movimentacoes)++;
            }
        
        }
        h = h / 3;
    }
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