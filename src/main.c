#include <stdio.h>

#include "../headers/funcionalidades.h"

/*
      ---------------------------------------------
    [  TRABALHO1 - ESTRUTURA DE DADOS III - 2023/2  ]
      ---------------------------------------------

    ->  Heitor Tanoue de Mello
        NUSP: 12547260
*/

int main () {
    int comando;
    scanf("%d", &comando);
    switch (comando) {
        case 1:
            createTable();
            break;
        case 2:
            selectFrom();
            break;
        case 3:
            selectWhere();
            break;
        case 4:
            selectRRN();
            break;
        default:
            break;
    }
}