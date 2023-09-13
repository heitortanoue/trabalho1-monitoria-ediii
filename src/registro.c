#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/registro.h"
#include "../headers/orgarquivos.h"
#include "../headers/io.h"
#define LIXO '$'

// Cria um novo registro e aloca memoria para suas strings
int criaRegistro (Registro *r) {
    r->removido = NAO_REMOVIDO;
    r->grupo = -1;
    r->popularidade = -1;
    r->peso = -1;
    r->tecnologiaOrigem.tamanho = 0;
    r->tecnologiaDestino.tamanho = 0;

    r->tecnologiaDestino.string = (char*) alocaMemoria(sizeof(char) * TAM_STRING);
    r->tecnologiaOrigem.string = (char*) alocaMemoria(sizeof(char) * TAM_STRING);

    return SUCESSO;
}

// Libera a memória alocada para um registro
int destroiRegistro (Registro *r) {
    free(r->tecnologiaDestino.string);
    free(r->tecnologiaOrigem.string);

    return SUCESSO;
}

// Copia toda a string, sem parar no '/0'
int copiaStringRegistro (char* destino, char* origem, int tam) {
    for (int i = 0; i < tam; i++) {
        destino[i] = origem[i];
    }
    return SUCESSO;
}

// Indica se o registro foi removido logicamente
int registroRemovido (Registro *r) {
    return r->removido == REMOVIDO;
}

void readline(char* string){
    char c = 0;

    do{
        c = (char) getchar();

    } while(c == '\n' || c == '\r');

    int i = 0;

    do{
        string[i] = c;
        i++;
        c = getchar();
    } while(c != '\n' && c != '\r');

    string[i]  = '\0';
}

//Leitura de cada campo no respectivo registro
int insereStringRegistro (char* str, char* str_registro, int tam_campo) {
    char campo_trunc[tam_campo];

    int tam_str = strlen(str) + 1;

    if (tam_campo > tam_str) {
        // Copia a string e preenche o resto com lixo
        int dif = tam_campo - tam_str;
        for (int i = 0; i < tam_str; i++) {
            campo_trunc[i] = str[i];
        }
        for (int i = 0; i < dif; i++) {
            campo_trunc[tam_str + i] = LIXO;
        }
    } else {
        // Corta o pedaço da string que não cabe no campo
        for (int i = 0; i < tam_campo - 1; i++) {
            campo_trunc[i] = str[i];
        }
        campo_trunc[tam_campo - 1] = '\0';
    }

    copiaStringRegistro(str_registro, campo_trunc, tam_campo);
    return SUCESSO;
}


void printNulo(){
    printf("NULO, ");
}
// Imprime todas as informações do registro
void imprimeRegistro (Registro *r ) {
    if (stringValida(r->tecnologiaOrigem.string)) {
        printf("%s, ", r->tecnologiaOrigem.string);
    } else printNulo();

    if (intValido(r->grupo)) {
        printf("%d, ", r->grupo);
    } else printNulo();

    if (intValido(r->popularidade)) {
        printf("%d, ", r->popularidade);
    } else printNulo();

    if (stringValida(r->tecnologiaDestino.string)) {
        printf("%s, ", r->tecnologiaDestino.string);
    } else printNulo();

    if (intValido(r->peso)) {
        printf("%d", r->peso);
    } else printf("NULO");

    printf("\n");
}

// Função auxiliar debugger para impressao do registro inteiro
void imprimeRegistroRaw (FILE* arq) {
    for (int i = 0; i < TAM_REGISTRO; i++) {
        char c = fgetc(arq);
        printf("%c", c);
    }
    printf("\n\n");
}

// Conta quantos registros há em um determinado arquivo
int contarRegistros (FILE *arq) {
    fseek(arq, 0, SEEK_END);
    long tamFinal = ftell(arq);
    fseek(arq, TAM_CABECALHO - 1, SEEK_SET);
    long tamInicial = ftell(arq);
    fseek(arq, 0, SEEK_SET);

    return (tamFinal - tamInicial) / TAM_REGISTRO;
}

// Calcula o ByteOffset de um registro atraves do seu RRN
int calculaByteoffset (int rrn){
    return (rrn  * TAM_REGISTRO) + TAM_CABECALHO;
}

//Funcao para alocar uma quantidade s na memoria e padronizar o tratamento de erro
void* alocaMemoria (size_t s) {
    void* ptr = malloc(s);
    if (ptr == NULL) {
        printf("Erro de alocacao de memoria\n");
        exit(1);
    }
    return ptr;
}