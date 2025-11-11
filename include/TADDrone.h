#ifndef TADDRONE_H
#define TADDRONE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADListaDePacotes.h"

// Definição do TAD Drone

typedef struct {
    int pesomaximo,
        pesocarregado,
        distanciadaviagem,
        distanciatotalpercorrida,
        nmrdeviagem;
    TListaDePacotes listadodrone;
} tdrone;

// Cabeçalho das Operações

void InicializarDrone (tdrone *drone, int pesomaximo); // Cria o Drone.
void CarregamentoDePacote (tdrone *drone, TPacote pacoteinserido); // Carrega o pacote da lista e insere no drone.
void RealizarEntrega (tdrone *drone, TListaDePacotes *lista); // Realiza as entregas de forma linear, do primeiro até o ultimo (Se aplica na distância percorrida).
void ImprimirDrone (tdrone drone); // Imprime todas as informações atuais do Drone.
void ImprimeViagens(TListaDePacotes* l); // Imprime as viagens que são executadas pelo drone.
void CalculaDistancia (TListaDePacotes* l, tdrone *drone); // Calcula a distância dos pacotes em uma lista.

#endif
