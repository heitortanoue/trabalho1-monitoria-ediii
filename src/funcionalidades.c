#include "../headers/funcionalidades.h"
#include "../headers/registro.h"
#include "../headers/orgarquivos.h"
#include "../headers/io.h"
#include "../headers/busca.h"
#include "../headers/cabecalho.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


// FUNCIONALIDADE 1 - Cria uma tabela com os campos especificados com base em um arquivo .CSV
int createTable (void) {
    char nome_arquivo_entrada[128];
    scanf("%s", nome_arquivo_entrada);
    char nome_arquivo_saida[128];
    scanf("%s", nome_arquivo_saida);

    // Abre o arquivo .csv de entrada
    FILE* csv = abreArquivo(nome_arquivo_entrada, "r");

	char cabecalho[128];
	fgets(cabecalho, 128, csv);

    // cria um novo cabeçalho e atualiza com as informações iniciais
    Cabecalho c;
    atualizarCabecalhoPadrao(&c);
	Registro r;
    criaRegistro(&r);

	// Cria o arquivo binário
	FILE* bin = abreArquivo(nome_arquivo_saida, "wb+");

	// Escreve o cabeçalho (no inicio do arquivo)
	escreveCabecalhoArquivo(bin, &c);

    // Leitura do arquivo .csv
    char linha[128];
    int numRegistros = 0, numTecnologias = 0;

    while (fgets(linha, 128, csv)) {
        lerCsvRegistro(&r, linha);
        inserirRegistroArquivo(bin, &r);
        c.proxRRN++;

        if (!tecnologiaCadastrada(bin, r.tecnologiaOrigem.string, numRegistros))
        {
            numTecnologias++;
        }

        if (!tecnologiaCadastrada(bin, r.tecnologiaDestino.string, numRegistros))
        {
            numTecnologias++;
        }

        numRegistros++;
    }

    // Atualiza o cabeçalho
    atualizarStatusCabecalho(&c, '1');
    atualizarContagensCabecalho(&c, numRegistros, numTecnologias);
    // Volta o cursor para o começo do arquivo
    fseek(bin, 0, SEEK_SET);
    escreveCabecalhoArquivo(bin, &c);

    destroiRegistro(&r);
    fclose(csv);
    fclose(bin);

    binarioNaTela(nome_arquivo_saida);

    return SUCESSO;
}

// FUNCIONALIDADE 2 - Imprime todos os registros de uma tabela
int selectFrom () {
    char nome_arquivo[128];
    scanf("%s", nome_arquivo);

    FILE* bin = abreArquivo(nome_arquivo, "rb");

    int qtdRegs = contarRegistros(bin);

    Cabecalho c;
    lerCabecalhoArquivo(bin, &c);

    Registro r;
    criaRegistro(&r);

    if (!qtdRegs) {
        printf("Registro inexistente.\n");
        return ERRO;
    }

    for (int i = 0; i < qtdRegs; i++) {
        if(lerRegistroArquivo(bin, &r) == SUCESSO){
            imprimeRegistro(&r);
        } else {
            continue;
        }
    }

    destroiRegistro(&r);
    fclose(bin);

    return SUCESSO;
}

//FUNCIONALIDADE 3 - Imprime todos os registros que contém o(s) campo(s) especificado(s)
int selectWhere (void){
    char nome_arquivo[128];
    scanf("%s", nome_arquivo);

    int qtd_filtros;
    scanf("%d", &qtd_filtros);

    Busca filtros;
    criaFiltro(&filtros, qtd_filtros);

    //salva os filtros na ordem
    for (int i = 0; i < qtd_filtros; i++){
        scanf("%s", (filtros.campo)[i]);
        getchar();
        scanTeclado((filtros.criterios)[i]); //entrada do teclado removendo aspas
        trataFiltros(&filtros, i); //identifica o campo
    }

    FILE* bin = abreArquivo(nome_arquivo, "rb");

    int qtdRegs = contarRegistros(bin);
    Cabecalho c;
    lerCabecalhoArquivo(bin, &c);

    Registro r;
    criaRegistro(&r);

    for (int i = 0; i < qtd_filtros; i++){
        for (int j = 0; j < qtdRegs; j++) {
            if(lerRegistroArquivo(bin, &r) == ERRO){
                continue;
            }

            if(testaRegistro(r, &filtros, i)){ //se tiver o campo de busca imprime
                imprimeRegistro(&r);
            }
        }

        fseek(bin, TAM_CABECALHO, SEEK_SET);
    }

    destroiFiltro(&filtros);
    destroiRegistro(&r);
    fclose(bin);

    return SUCESSO;
}

// FUNCIONALIDADE 4 - Imprime o registro de RRN especificado
int selectRRN (void) {
    char nome_arquivo[128];
    scanf("%s", nome_arquivo);

    int rrn;
    scanf("%d", &rrn);

    FILE* bin = abreArquivo(nome_arquivo, "rb");

    Cabecalho c;
    lerCabecalhoArquivo(bin, &c);

    Registro r;
    criaRegistro(&r);

    if (rrn >= c.proxRRN) {
        printf("Registro inexistente.\n");
        return ERRO;
    }

    fseek(bin, calculaByteoffset(rrn), SEEK_SET);

    if(lerRegistroArquivo(bin, &r) == SUCESSO){
        imprimeRegistro(&r);
    } else {
        printf("Registro inexistente.\n");
        return ERRO;
    }

    destroiRegistro(&r);
    fclose(bin);

    return SUCESSO;
}