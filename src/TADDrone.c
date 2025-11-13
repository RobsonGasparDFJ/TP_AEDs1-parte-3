#include "../include/TADDrone.h"
#include "../include/TADListaDePacotes.h"
#include "../include/TADGalpao.h"
#include "../include/TADPacote.h" 


void InicializarDrone (tdrone *drone, int pesomaximo) {
    drone->pesomaximo = pesomaximo;
    drone->pesocarregado = 0;
    drone->distanciadaviagem = 0;
    drone->distanciatotalpercorrida = 0;
    drone->nmrdeviagem = 1;
    fazListaVazia(&(drone->listadodrone));
}

void CarregamentoDePacote (tdrone *drone, TPacote pacoteinserido) {
    pacoteinserido = PacoteTransportado;
    insereFinal (&(drone->listadodrone), pacoteinserido);
    drone->pesocarregado += pacoteinserido.peso;
    //printf("\nPacote para %s foi pego pelo drone.", PacoteTransportado.destinatario);
}

void RealizarEntrega (tdrone *drone, TListaDePacotes *lista) {
    printf("\nViagem %d\n", drone->nmrdeviagem);
    ImprimeViagens(&(drone->listadodrone));
    CalculaDistancia(&(drone->listadodrone),drone);
    fazListaVazia(&(drone->listadodrone));
    drone->distanciatotalpercorrida += drone->distanciadaviagem;
    drone->distanciadaviagem = 0;
    drone->nmrdeviagem++;
}

void ImprimirDrone (tdrone drone) {
    printf("\n ------------------------------- \n");
    printf("-- INFORMACOES DO DRONE --\n");
    printf(" Peso maximo: %d\n", drone.pesomaximo);
    printf(" Peso sendo carregado: %d\n", drone.pesocarregado);
    printf("\n ------------------------------- \n");
    imprimeLista(&(drone.listadodrone));
}

void ImprimeViagens(TListaDePacotes* l){
    if(l->primeiro == l->ultimo){
        return;
    }
    celula* aux;
    aux = l->primeiro->prox;
    while(aux!=NULL){
            printf("Entrega: %s para %s com prioridade %d\n",getConteudo(&aux->p),getDestinatario(&aux->p),getPrioridade(&aux->p));
        aux = aux->prox;
    }
}

void CalculaDistancia (TListaDePacotes* l, tdrone *drone){
    drone->distanciadaviagem = 0;
    if (l->primeiro == l->ultimo) {
        return;
    }
    celula* aux = l->primeiro->prox;
    celula* anterior = NULL;

    if (aux != NULL && aux->prox == NULL) { // Só um pacote: ida e volta.
        drone->distanciadaviagem = aux->p.distancia * 2;
    } else { // Mais de um pacote
        drone->distanciadaviagem += aux->p.distancia; // Ida ao primeiro
        anterior = aux; // Armazena o valor desse, que se torna o anterior.
        aux = aux->prox; // Passando para o proximo.
        while (aux != NULL) { // Enquanto a lista ter algum elemento :
            drone->distanciadaviagem += abs(aux->p.distancia - anterior->p.distancia); // Soma diferença entre o pacote sendo lido e o anterior.
            anterior = aux; // Armazena novamente.
            aux = aux->prox; // Lê o proximo.
        }
        drone->distanciadaviagem += anterior->p.distancia; // Volta do último até o ponto inicial
    }
    printf("Distancia Total: %dkm\n", drone->distanciadaviagem); // Printa a distância total da viagem.
}