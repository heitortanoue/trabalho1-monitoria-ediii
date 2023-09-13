#ifndef __REGISTRO_H__
#define __REGISTRO_H__

#include "cabecalho.h"
#include <stdio.h>

// Quantidade de bytes do registro de dados
#define TAM_REGISTRO 76
// Quantidade de bytes a serem alocados para manipulacao de strings
#define TAM_STRING 128
// Quantidade de bytes da parte fixa do registro
#define TAM_REGISTRO_FIXO 21

// Caractere padrao para preencher bytes vazios do registro
#define LIXO '$'
// Caracteres padrao para remocao logica
#define REMOVIDO '1'
#define NAO_REMOVIDO '0'

typedef struct {
    int tamanho;
    char* string;
} StringVariavel;

// tamanho fixo de 76 bytes
typedef struct {
    // campos de controle
    char removido;

    // conteudo
    int grupo;
    int popularidade;
    int peso;
    StringVariavel tecnologiaOrigem;
    StringVariavel tecnologiaDestino;
} Registro;

typedef struct{
    char **campo;
    char **criterios;
    int qtdFiltros;
    int *tipo_campo;
    long pagDisco; //pag de disco acessadas
} Busca;

int criaRegistro (Registro *r);
int destroiRegistro (Registro *r);

int insereStringRegistro (char* str, char* str_registro, int tam_campo);
void imprimeRegistro (Registro *r);
int registroRemovido (Registro *r);
void readline(char* string);

int contarRegistros (FILE *arq);
int calculaByteoffset (int rrn);

void imprimeRegistroRaw (FILE* arq);
void* alocaMemoria (size_t s);

#endif