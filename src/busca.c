#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/orgarquivos.h"
#include "../headers/registro.h"
#include "../headers/csv.h"
#include "../headers/busca.h"

// Cria a struct dos dados de busca
int criaFiltro(Busca *filtros, int qtd){
	filtros->pagDisco = 0; //paginas de discos acessadas
	filtros->qtdFiltros = qtd; //num. de criterios de busca

	filtros->tipo_campo = (int*) alocaMemoria(sizeof(int) * qtd); //id dos campos
	filtros->campo = (char**) alocaMemoria(sizeof(char *) * qtd);  //campos string
    for (int i = 0; i < qtd; i++){
        filtros->campo[i] = (char*) alocaMemoria(sizeof(char) * 128);
    }

	filtros->criterios = (char**) alocaMemoria(sizeof(char *) * qtd); //valores string
    for (int i = 0; i < qtd; i++){
        filtros->criterios[i] = (char*) alocaMemoria(sizeof(char) * 128);
    }

	return SUCESSO;
}

// Desaloca a struct de busca
int destroiFiltro(Busca *filtros){
	free(filtros->tipo_campo);

    for (int i = 0; i < filtros->qtdFiltros; i++){
        free(filtros->campo[i]);
    }
	free(filtros->campo);

    for (int i = 0; i < filtros->qtdFiltros; i++){
        free(filtros->criterios[i]);
    }
	free(filtros->criterios);
		
	return SUCESSO;
}

// Trata os filtros identificando o campo e o criterio
int trataFiltros(Busca *filtros, int i){
	if(!strcmp((filtros->campo)[i], "idConecta")) (filtros -> tipo_campo)[i] = 0;
	if(!strcmp((filtros->campo)[i], "nomePoPs")) (filtros -> tipo_campo)[i] = 1;
	if(!strcmp((filtros->campo)[i], "nomePais")) (filtros -> tipo_campo)[i] = 2;
	if(!strcmp((filtros->campo)[i], "siglaPais")) (filtros -> tipo_campo)[i] = 3;
	if(!strcmp((filtros->campo)[i], "idPoPsConectado")) (filtros -> tipo_campo)[i] = 4;
	if(!strcmp((filtros->campo)[i], "velocidade")) (filtros -> tipo_campo)[i] = 5;
    if(!strcmp((filtros->campo)[i], "unidadeMedida")) (filtros -> tipo_campo)[i] = 6;

	return SUCESSO;
}

// Compara o registro com o critério de busca - return 1 se for compativel com o criterio 0 se nao
int testaRegistro (Registro reg, Busca *filtro, int numFiltro){
	int valido = 0;
	if (registroRemovido(&reg)){
		return 0;
	} else {
		switch (filtro->tipo_campo[numFiltro])
		{
		case 0:
			if (reg.idConecta == atoi(filtro->criterios[numFiltro])) valido = 1;
			break;
		case 1:
			if (!strcmp(reg.nomePoPs, filtro->criterios[numFiltro])) valido = 1;
			break;
		case 2:
			if (!strcmp(reg.nomePais, filtro->criterios[numFiltro])) valido = 1;
			break;
		case 3:
			if (!strcmp(reg.siglaPais, filtro->criterios[numFiltro])) valido = 1;
			break;
		case 4:
			if (reg.idPoPsConectado == atoi(filtro->criterios[numFiltro])) valido = 1;
			break;
		case 5:
			if (reg.velocidade == atoi(filtro->criterios[numFiltro])) valido = 1;
			break;
        case 6:
            if (reg.unidadeMedida == validaChar(filtro->criterios[numFiltro])) valido = 1;
            break;
		default:
			break;
		}
		return valido;
	}
}