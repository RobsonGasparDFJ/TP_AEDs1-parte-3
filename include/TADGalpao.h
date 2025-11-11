#ifndef TADDGALPAO_H
#define TADDGALPAO_H

#include "TADDrone.h"
#include "TADListaDePacotes.h"
#include "TADPacote.h"

//O galpão contendo a Lista De Pacotes
typedef struct{
    TListaDePacotes ListaDePacotes;
}TGalpao;

// Variável a ser utilizada para armazenar o pacote removido do galpão (função CarregamentoDePacote), essa variável é puxada pela função do Drone...
extern TPacote PacoteTransportado;

//Operações do Galpão
void InicializarGalpao(TGalpao *Galpao);//Inicializa um Lista dentro do galpão.
void RecebimentoDePacote(TGalpao *Galpao,TPacote pacote);//Recebe os pacotes e insere ataves das funcções de ListaDePacotes.
void EntregaDoDia(TGalpao *Galpao);//Chama a função que printa todo ListaDePacotes.
void CarregamentoDePacotes(TGalpao *Galpao); // //Insere o pacote no drone para entrega, e retira o mesmo do galpão.

#endif
