
# Arquivos binários
> *Trabalho 1 de Estrutura de Dados III (SCC0607) - 2023/2*


![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

Este trabalho tem como objetivo armazenar dados em um arquivo binário, bem como desenvolver funcionalidades para a manipulação desses dados.


## Estrutura

O arquivo final é composto por um cabeçalho (que ocupa uma página de disco inteira) e *n* registros.
```c
// Quantidade de bytes do registro de dados
#define TAM_REGISTRO 76
// Quantidade de bytes a serem alocados para manipulacao de strings
#define TAM_STRING 128
// Quantidade de bytes da parte fixa do registro
#define TAM_REGISTRO_FIXO 21
```
```c
// Caractere padrao para preencher bytes vazios do registro
#define LIXO '$'
// Caracteres padrao para remocao logica
#define REMOVIDO '1'
#define NAO_REMOVIDO '0'
```

### Cabeçalho

O registro de cabeçalho deve conter os seguintes campos:
- *status*: indica se o arquivo de dados está consistente. Pode assumir os valores ‘0’ (inconsistente) ou ‘1’ (consistente).
- *proxRRN*: indica o próximo RRN a ser inserido no arquivo de dados.
- *nroTecnologias*: indica o número de tecnologias únicas (de Origem) presentes no arquivo de dados.
- *nroParesTecnologias*: indica o número de registros de dados presentes no arquivo de dados.

#### Estrutura do cabeçalho
```c
// Tamanho fixo de 13 bytes
typedef struct {
    char status;
    int proxRRN;
    int nroTecnologias;
    int nroParesTecnologias;
} Cabecalho;
```

### Registros

Os registros de dados são de tamanho fixo, com campos de tamanho fixo e campos de tamanho variável. Para os campos de tamanho variável, deve ser especificado o tamanho.
Os campos de tamanho fixo são definidos da seguinte forma:
- *grupo*: inteiro de 4 bytes.
- *popularidade*: inteiro de 4 bytes.
- *peso*: inteiro de 4 bytes.
- *tamanhoTecnologiaOrigem*: inteiro de 4 bytes.
- *tamanhoTecnologiaDestino*: inteiro de 4 bytes.

Os campos de tamanho variável são definidos da seguinte forma:
- *tecnologiaOrigem*: string de tamanho variável.
- *tecnologiaDestino*: string de tamanho variável.

Adicionalmente, os seguintes campos de tamanho fixo também compõem cada registro. Esses campos de controle são necessários para o gerenciamento de registros logicamente removidos.
- *removido*: indica se o registro está logicamente removido. Pode assumir os valores ‘1’, para indicar que o registro está marcado como logicamente removido, ou ‘0’, para indicar que o registro não está marcado como removido.

#### Estrutura do registro
```c
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
```
## Funcionalidades

### Create Table
Cria uma tabela com os campos especificados com base em um arquivo .CSV e gera de saída um arquivo .BIN
```
1 [nome-arquivo-entrada-csv] [nome-arquivo-saida-bin]
```
A saída é o valor da função binarioNaTela, cedida pela professora para correção do trabalho.

### Select From
Imprime todos os registros de uma arquivo .BIN
```
2 [nome-arquivo-entrada-bin]
```
Exemplo de saída:
```
OBJECTIVE-C, 4, 47, XCODE, 5
SWIFT, 4, 64, XCODE, 6
IPHONE, 4, 15, XCODE, 4
IOS, 4, 87, XCODE, 6
JSON, 6, 25, XML, 44
```

### Select Where
Imprime todos os registros que contém o(s) campo(s) especificado(s).
```
3 [nome-arquivo-entrada-bin] [quantidade-de-filtros]
[campo1] [valor1]
[...] [...]
```
Exemplo de entrada onde são filtrados os registros com campos grupo == 3,
popularidade == 14 e nomeTecnologiaOrigem == "AZURE"

```
3 binario8.bin 3
grupo 3
popularidade "14"
nomeTecnologiaOrigem "AZURE"
```

### Select RRN
Imprime o registro de um determinado RRN.
```
4 [nome-arquivo-entrada-bin] [RRN]
```


## Rodando localmente

Clone o projeto

```bash
  git clone https://github.com/heitortanoue/trabalho1-monitoria-ediii
```

Compile o código

```bash
  make all
```

Rode o código

```bash
  make run
```


## Autor

- [@heitortanoue](https://www.github.com/heitortanoue)


## Licença

[MIT](https://choosealicense.com/licenses/mit/)
