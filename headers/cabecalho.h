#ifndef __CABECALHO_H__
#define __CABECALHO_H__

#include <stdio.h>

// Quantidade de bytes do cabeçalho
#define TAM_CABECALHO 13

// Tamanho fixo de 13 bytes
typedef struct {
    char status;
    int proxRRN;
    int nroTecnologias;
    int nroParesTecnologias;
} Cabecalho;

int atualizarCabecalhoPadrao (Cabecalho *c);
int atualizarStatusCabecalho (Cabecalho *c, char status);
int atualizarContagensCabecalho (Cabecalho *c, int numRegistros, int numTecnologias);
int lerCabecalhoArquivo (FILE *arq, Cabecalho *c);
int testaStatusCabecalho (Cabecalho *c);
void imprimeCabecalho (Cabecalho *c);

#endif