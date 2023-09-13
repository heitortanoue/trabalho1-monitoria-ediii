#include "../headers/cabecalho.h"
#include "../headers/orgarquivos.h"
#include <math.h>

// Atualiza o cabeçalho com as informações default
int atualizarCabecalhoPadrao (Cabecalho *c ) {
	c->status = '0';
    c->proxRRN = 0;
    c->nroTecnologias = 0;
    c->nroParesTecnologias = 0;

    return SUCESSO;
}

// Atualiza o status do cabeçalho com o parametro 'status'
int atualizarStatusCabecalho (Cabecalho *c, char status) {
    c->status = status;
    return SUCESSO;
}

int testaStatusCabecalho (Cabecalho *c) {
    if (c->status == '0') {
        printf("Falha no processamento do arquivo.\n");
        return ERRO;
    }
    return SUCESSO;
}

int atualizarContagensCabecalho(Cabecalho *c, int numRegistros, int numTecnologias)
{
    c->nroParesTecnologias = numRegistros;
    c->nroTecnologias = numTecnologias;
    return SUCESSO;
}

// Lê o cabeçalho do arquivo 'arq' e armazena no Cabecalho 'c'
int lerCabecalhoArquivo (FILE *arq, Cabecalho *c) {
    fread(&c->status, sizeof(char), 1, arq);
    fread(&c->proxRRN, sizeof(int), 1, arq);
    fread(&c->nroTecnologias, sizeof(int), 1, arq);
    fread(&c->nroParesTecnologias, sizeof(int), 1, arq);

    if (testaStatusCabecalho(c) == ERRO) {
        exit(ERRO);
    }

    return SUCESSO;
}

void imprimeCabecalho (Cabecalho *c) {
    printf("Status: %c\n", c->status);
    printf("RRN Prox: %d\n", c->proxRRN);
    printf("Nro Tecnologias: %d\n", c->nroTecnologias);
    printf("Nro Pares Tecnologias: %d\n", c->nroParesTecnologias);
}