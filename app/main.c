#include <stdio.h>
#include <stdlib.h>
#include "../include/TADDrone.h"
#include "../include/TADGalpao.h"
#include "../include/TADListaDePacotes.h"
#include "../include/TADPacote.h"

int main(){
    // Menu de inserção de dados.
    printf("\n----------------------------------------------\n");
    printf("Escolha um modo para inserir dados:\n");

    int escolhainicial;
    while (1) {
        printf("Digite sua escolha (1 - Inserir Dados Manualmente || 2 - Inserir Arquivo):\n");

        if (scanf("%d", &escolhainicial) == 1 && (escolhainicial == 1 || escolhainicial == 2)) {
        break;
        }

        printf("\nOpcao invalida, escolha novamente.\n");
        while(getchar() != '\n');
    }

    if (escolhainicial == 1) {

        tdrone dronemanual;
        int manualpesomaximo, numdepacotesmanual;
        printf("Digite o peso maximo do seu drone:\n");
        scanf("%d", &manualpesomaximo);
        printf("Digite o numero de pacotes que vai inserir:\n");
        scanf("%d", &numdepacotesmanual);
        InicializarDrone(&dronemanual, manualpesomaximo);

        TGalpao galpao;
        InicializarGalpao(&galpao);

        TPacote pacotemanual;
        inicializar(&pacotemanual);
        printf("Digite para cada pacote: conteudo, destinatario, peso, distancia de entrega:\n");
        for (int i=0 ; i<numdepacotesmanual; i++){
            scanf("%99s %99s %d %d %d",
                pacotemanual.conteudo,
                pacotemanual.destinatario,
                &pacotemanual.peso,
                &pacotemanual.distancia,&pacotemanual.prioridade);
            RecebimentoDePacote(&galpao, pacotemanual);
            // printf("\n Pacote %d de %s recebido com sucesso!\n", i+1, pacotemanual.destinatario);
        }
        //Ordena a lista do galpão========
         Shellsort(&galpao);
         //printf("ordenou");
        //================================
        while (galpao.ListaDePacotes.primeiro != galpao.ListaDePacotes.ultimo) {
            CarregamentoDePacotes(&galpao); // Galpão libera pacote.
                if (dronemanual.pesocarregado + PacoteTransportado.peso > manualpesomaximo){ // Verifica se pelo peso consegue pegar.
                    RealizarEntrega(&dronemanual, (&(dronemanual.listadodrone)));
                    dronemanual.pesocarregado = 0;
            }
            CarregamentoDePacote(&dronemanual, PacoteTransportado); // Drone pega pacote.
        }
        if (dronemanual.pesocarregado > 0) {
            RealizarEntrega(&dronemanual, (&(dronemanual.listadodrone)));
            dronemanual.pesocarregado = 0;
        }
        printf ("\nTotal de Quilometros Percorridos no Dia: %dkm\n", dronemanual.distanciatotalpercorrida);
    }

    FILE *arquivo;
    char nomearquivo[100];
    char linha [100];

    if (escolhainicial == 2){

        while (1) {
            printf("\nDigite o nome do arquivo a ser lido:\n");
            scanf("%s", nomearquivo);

            arquivo = fopen(nomearquivo, "r"); // Tenta abrir o arquivo.
            if(arquivo != NULL) {
                break;
            }
            printf("\nErro ao abrir o arquivo.\n");
        }

        tdrone dronearquivo;
        int arquivopesomaximo, numdepacotes;
        fscanf(arquivo, "%d", &arquivopesomaximo);
        fscanf(arquivo, "%d", &numdepacotes);
        InicializarDrone(&dronearquivo, arquivopesomaximo);

        TGalpao galpao;
        InicializarGalpao(&galpao);

        TPacote pacotearquivo;
        inicializar(&pacotearquivo);
        for (int i=0 ; i<numdepacotes; i++){
            fscanf(arquivo, "%99s %99s %d %d %d",
                pacotearquivo.conteudo,
                pacotearquivo.destinatario,
                &pacotearquivo.peso,
                &pacotearquivo.distancia,&pacotearquivo.prioridade);
            RecebimentoDePacote(&galpao, pacotearquivo);
            // printf("\n Pacote %d de %s recebido com sucesso!\n", i+1, pacotearquivo.destinatario);
        }

        //Ordena a lista do galpão========
          Shellsort(&galpao);
          //printf("ordenou");
        //================================

        while (galpao.ListaDePacotes.primeiro != galpao.ListaDePacotes.ultimo) {
            CarregamentoDePacotes(&galpao); // Galpão libera pacote.
                if (dronearquivo.pesocarregado + PacoteTransportado.peso > arquivopesomaximo){ // Verifica se pelo peso consegue pegar.
                    RealizarEntrega(&dronearquivo, (&(dronearquivo.listadodrone)));
                    dronearquivo.pesocarregado = 0;
            }
            CarregamentoDePacote(&dronearquivo, PacoteTransportado); // Drone pega pacote.
        }
        if (dronearquivo.pesocarregado > 0) {
            RealizarEntrega(&dronearquivo, &(dronearquivo.listadodrone));
            dronearquivo.pesocarregado = 0;
        }
        printf ("\nTotal de Quilometros Percorridos no Dia: %dkm\n\n", dronearquivo.distanciatotalpercorrida);
    }


    return 0;
}
