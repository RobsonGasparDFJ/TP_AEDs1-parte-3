#ifndef PACOTE_H
#define PACOTE_H

#include <stdio.h>
#include <stdlib.h>
/*definicao do TAD pacote..*/
typedef struct {
    char conteudo[100];
    char destinatario[100];
    int peso,distancia,prioridade;
}TPacote;

/*Funcao de inicializar*/
void inicializar(TPacote* p);

/*Funcoes de atribuicao (set) dos atributos de pacote*/
void setConteudo(TPacote* p,char* c);
void setDestinatario(TPacote* p,char* n);
void setPeso(TPacote* p,int x);
void setDistancia(TPacote* p,int d);
void setPrioridade(TPacote* p,int u);

/*Funcoes de obtencao (get) dos atributos de pacote*/
char* getConteudo(TPacote* p);
char* getDestinatario(TPacote* p);
int getPeso(TPacote* p);
int getDistancia(TPacote* p);
int getPrioridade(TPacote* p);

#endif
