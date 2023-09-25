#include "../headers/io.h"
#include "../headers/registro.h"
#include "../headers/orgarquivos.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Lê uma 'linha' do arquivo .csv, valida os dados e insere no registro 'r'
int lerCsvRegistro (Registro *r, char *linha) {
    char *temp = (char*) alocaMemoria(sizeof(char) * 64);

    meuStrtok(temp, linha, ',');
    strcpy(r->tecnologiaOrigem.string, validaString(temp));
    if (stringValida(r->tecnologiaOrigem.string)) {
        r->tecnologiaOrigem.tamanho = strlen(r->tecnologiaOrigem.string);
    } else {
        r->tecnologiaOrigem.tamanho = 0;
    }

    meuStrtok(temp, linha, ',');
    r->grupo = validaInt(temp);

    meuStrtok(temp, linha, ',');
    r->popularidade = validaInt(temp);

    meuStrtok(temp, linha, ',');
    strcpy(r->tecnologiaDestino.string, validaString(temp));
    if (stringValida(r->tecnologiaDestino.string)) {
        r->tecnologiaDestino.tamanho = strlen(r->tecnologiaDestino.string);
    } else {
        r->tecnologiaDestino.tamanho = 0;
    }

    meuStrtok(temp, linha, ',');
    r->peso = validaInt(temp);

    free(temp);

    return SUCESSO;
}

// Faz o parse de uma linha, como se fosse a função split de outras linguagens
// Retorna em 'pedaço' a substring da linha até o delimitador
// Retorna em 'linha' o resto da linha
void meuStrtok (char* pedaco, char *str, char delim) {
    int i = 0;
    // Enquanto a string não acabar e não encontrar o delimitador, copiar para o pedaco
    while (str[i] != delim && str[i] != '\0') {
        pedaco[i] = str[i];
        i++;
    }

    // Remocao de espaco final
    if (pedaco[i - 1] == ' ') {
        pedaco[i - 1] = '\0';
    } else {
        pedaco[i] = '\0';
    }

    // Para evitar multiplos delimitadores seguidos
    if (str[i] == delim) {
        i++;
    }

    // Copia o resto da string para a string original
    int j = 0;
    while (str[i] != '\0') {
        str[j] = str[i];
        i++;
        j++;
    }
    str[j] = '\0';
}

// As funções abaixo tornam válidas as informações lidas do arquivo .csv

// Deixa uma string no padrao de validacao
char* validaString (char* str) {
    return str && strlen(str) ? str : "*";
}
// Deixa um int no padrao de validacao
int validaInt (char* i) {
    return i && intValido(atoi(i)) ? atoi(i) : -1;
}
// Deixa um char no padrao de validacao
char validaChar (char* c) {
    return c && c[0] != '\0' ? c[0] : '*';
}

// As funções abaixo verificam a validade das informações

// Verifica se uma string é válida
int stringValida (char* str) {
    return str && str[0] && str[0] != '*';
}
// Verifica se um int é válido
int intValido (int i) {
    return i > 0;
}
// Verifica se um char é válido
int charValido (char c) {
    return c != '*';
}

// Le um campo do novo registro removendo as aspas
void scanTeclado(char *strDest)
{
    char c = getchar();
    if (c != '\"')
    { // se for uma entrada sem aspas le ate o proximo espaco, enter ou valor invalido
        int i = 0;
        while ((c != ' ' && c != '\n') || (c > 32 && c < 126))
        {
            if (i > 60)
            {
                break;
            }
            strDest[i] = c;
            c = getchar();
            i++;
        }
        strDest[i] = '\0';
    }
    else
    { // se for uma entrada com aspas le ate a proxima aspas
        int i = 0;
        c = getchar();
        while (c != '\"')
        {
            if (i > 60)
            {
                break;
            }
            strDest[i] = c;
            c = getchar();
            i++;
        }
        getchar();
        strDest[i] = '\0';
    }
}