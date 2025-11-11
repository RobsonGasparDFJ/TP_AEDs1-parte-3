#include <stdio.h>
#include <stdlib.h>
#include "../include/TADPacote.h"
#include <string.h>

/*implementacao da inicializacao do pacote*/
void inicializar(TPacote* p){
    strcpy(p->conteudo,"");
    strcpy(p->destinatario,"");
    p->distancia = 0;
    p->peso = 0;
};

/*implementacao de atribuicao dos atributos do pacote*/
void setConteudo(TPacote* p,char* c){
    strcpy(p->conteudo,c);
};
void setDestinatario(TPacote* p,char* n){
    strcpy(p->destinatario,n);
};
void setPeso(TPacote* p,int x){
    p->peso = x;
};
void setDistancia(TPacote* p,int d){
    p->distancia = d;
};

/*implementacao de atribuicao dos atributos do pacote*/
char* getConteudo(TPacote* p){
    return p->conteudo;
};
char* getDestinatario(TPacote* p){
    return p->destinatario;
};
int getPeso(TPacote* p){
    return p->peso;
};
int getDistancia(TPacote* p){
    return p->distancia;
};
