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