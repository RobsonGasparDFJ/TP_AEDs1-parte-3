#include <stdio.h>
#include <stdlib.h>
#include "../include/TADDrone.h"
#include "../include/TADGalpao.h"
#include "../include/TADListaDePacotes.h"
#include "../include/TADPacote.h"
#include <time.h>

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

        TGalpao galpaoShell;
        TGalpao galpaoSelection;
        InicializarGalpao(&galpaoShell);
        InicializarGalpao(&galpaoSelection);

        TPacote pacotemanual;
        inicializar(&pacotemanual);
        printf("Digite para cada pacote: conteudo, destinatario, peso, distancia de entrega:\n");
        for (int i=0 ; i<numdepacotesmanual; i++){
            scanf("%99s %99s %d %d %d",
                pacotemanual.conteudo,
                pacotemanual.destinatario,
                &pacotemanual.peso,
                &pacotemanual.distancia,
                &pacotemanual.prioridade);
            RecebimentoDePacote(&galpaoShell, pacotemanual);
            RecebimentoDePacote(&galpaoSelection, pacotemanual);
            // printf("\n Pacote %d de %s recebido com sucesso!\n", i+1, pacotemanual.destinatario);
        }
        //armazera o tempo de execucao das funcoes
        clock_t inicio,fim;
        double tempoShell,tempoSelection;

        //Ordena a lista do galpao das duas maneiras possiveis,respectivamente selection e shell (medindo o tempo)
        int comparacoesSelection =0;
        int movimentacoesSelection =0;
        inicio = clock();
        SelectionSort(&galpaoSelection,&comparacoesSelection, &movimentacoesSelection);
        fim = clock();
        tempoSelection = (double)(fim-inicio)/CLOCKS_PER_SEC;

        int comparacoesShell = 0;
        int movimentacoesShell = 0;

        inicio = clock();
        Shellsort(&galpaoShell,&comparacoesShell,&movimentacoesShell);
        fim = clock();
        tempoShell = (double)(fim-inicio)/CLOCKS_PER_SEC;
        //imprime a quantidade de tempo de execucao,comparacoes e troca de cada tipo

        FILE *arquivo_de_saida;
        arquivo_de_saida = fopen("saida.txt","w");
        fprintf(arquivo_de_saida,"\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=INFORMACOES DOS ALGORITMOS DE ORDENACAO+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
        fprintf(arquivo_de_saida,"SELECTION: tempo de execucao: %.5lf s | Comparacoes: %d | Movimentacoes: %d\n", 
       tempoSelection, comparacoesSelection, movimentacoesSelection);
       fprintf(arquivo_de_saida,"SHELLSORT: tempo de execucao: %.5lf s | Comparacoes: %d | Movimentacoes: %d\n", 
       tempoShell, comparacoesShell, movimentacoesShell);

       fclose(arquivo_de_saida);
        //imprime as viagens com selecao
        FILE *anexo_da_saida = freopen("saida.txt","a",stdout);
        printf("\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=VIAGENS ORDENADAS POR SELECTION+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
        while (galpaoSelection.ListaDePacotes.primeiro != galpaoSelection.ListaDePacotes.ultimo) {
            CarregamentoDePacotes(&galpaoSelection); // Galpão libera pacote.
                if (dronemanual.pesocarregado + PacoteTransportado.peso > manualpesomaximo){ // Verifica se pelo peso consegue pegar.
                    RealizarEntrega(&dronemanual, (&(dronemanual.listadodrone)));
                    dronemanual.pesocarregado = 0;
            }
            CarregamentoDePacote(&dronemanual, PacoteTransportado); // Drone pega pacote.
        }
        if (dronemanual.pesocarregado > 0) {
            RealizarEntrega(&dronemanual, &(dronemanual.listadodrone));
            dronemanual.pesocarregado = 0;
        }
        printf ("\nTotal de Quilometros Percorridos no Dia: %dkm\n\n", dronemanual.distanciatotalpercorrida);
        printf("\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=VIAGENS ORDENADAS POR SHELLSORT+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
        dronemanual.nmrdeviagem = 1;
        dronemanual.distanciatotalpercorrida = 0;
        //imprime as viagens com o algoritmo shellsort
        while (galpaoShell.ListaDePacotes.primeiro != galpaoShell.ListaDePacotes.ultimo) {
            CarregamentoDePacotes(&galpaoShell); // Galpão libera pacote.
                if (dronemanual.pesocarregado + PacoteTransportado.peso > manualpesomaximo){ // Verifica se pelo peso consegue pegar.
                    RealizarEntrega(&dronemanual, (&(dronemanual.listadodrone)));
                    dronemanual.pesocarregado = 0;
            }
            CarregamentoDePacote(&dronemanual, PacoteTransportado); // Drone pega pacote.
        }
        if (dronemanual.pesocarregado > 0) {
            RealizarEntrega(&dronemanual, &(dronemanual.listadodrone));
            dronemanual.pesocarregado = 0;
        }
        printf ("\nTotal de Quilometros Percorridos no Dia: %dkm\n\n", dronemanual.distanciatotalpercorrida);
        fclose(anexo_da_saida);
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

        TGalpao galpaoShell;//galpao que sera organizado por algoritmo de ordenacao shell
        TGalpao galpaoSelection;//galpao que sera organizado por algoritmo de ordenacao de selacao
        InicializarGalpao(&galpaoShell);
        InicializarGalpao(&galpaoSelection);


        TPacote pacotearquivo;
        inicializar(&pacotearquivo);
        for (int i=0 ; i<numdepacotes; i++){
            fscanf(arquivo, "%99s %99s %d %d %d",
                pacotearquivo.conteudo,
                pacotearquivo.destinatario,
                &pacotearquivo.peso,
                &pacotearquivo.distancia,
                &pacotearquivo.prioridade);
            RecebimentoDePacote(&galpaoSelection, pacotearquivo);
            RecebimentoDePacote(&galpaoShell, pacotearquivo);
            // printf("\n Pacote %d de %s recebido com sucesso!\n", i+1, pacotearquivo.destinatario);
        }
        //armazera o tempo de execucao das funcoes
        clock_t inicio,fim;
        double tempoShell,tempoSelection;

        //Ordena a lista do galpao das duas maneiras possiveis,respectivamente selection e shell (medindo o tempo)
        int comparacoesSelection =0;
        int movimentacoesSelection =0;
        inicio = clock();
        SelectionSort(&galpaoSelection,&comparacoesSelection, &movimentacoesSelection);
        fim = clock();
        tempoSelection = (double)(fim-inicio)/CLOCKS_PER_SEC;

        int comparacoesShell = 0;
        int movimentacoesShell = 0;

        inicio = clock();
        Shellsort(&galpaoShell,&comparacoesShell,&movimentacoesShell);
        fim = clock();
        tempoShell = (double)(fim-inicio)/CLOCKS_PER_SEC;
        //imprime a quantidade de tempo de execucao,comparacoes e troca de cada tipo

        FILE *arquivo_de_saida;
        arquivo_de_saida = fopen("saida.txt","w");
        fprintf(arquivo_de_saida,"\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=INFORMACOES DOS ALGORITMOS DE ORDENACAO+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
        fprintf(arquivo_de_saida,"SELECTION: tempo de execucao: %.5lf s | Comparacoes: %d | Movimentacoes: %d\n", 
       tempoSelection, comparacoesSelection, movimentacoesSelection);
       fprintf(arquivo_de_saida,"SHELLSORT: tempo de execucao: %.5lf s | Comparacoes: %d | Movimentacoes: %d\n", 
       tempoShell, comparacoesShell, movimentacoesShell);

       fclose(arquivo_de_saida);
        //imprime as viagens com selecao
        FILE *anexo_da_saida = freopen("saida.txt","a",stdout);
        printf("\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=VIAGENS ORDENADAS POR SELECTION+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
        while (galpaoSelection.ListaDePacotes.primeiro != galpaoSelection.ListaDePacotes.ultimo) {
            CarregamentoDePacotes(&galpaoSelection); // Galpão libera pacote.
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
        printf("\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=VIAGENS ORDENADAS POR SHELLSORT+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
        dronearquivo.nmrdeviagem = 1;
        dronearquivo.distanciatotalpercorrida = 0;
        //imprime as viagens com o algoritmo shellsort
        while (galpaoShell.ListaDePacotes.primeiro != galpaoShell.ListaDePacotes.ultimo) {
            CarregamentoDePacotes(&galpaoShell); // Galpão libera pacote.
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
        fclose(anexo_da_saida);
    }


    return 0;
}
