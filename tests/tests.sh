#!/bin/bash

# Certifique-se de que as pastas 'out', 'public' e 'private' existem
mkdir -p ./out ./public ./private

# Defina o número total de testes
num_tests=10

# Array de números de teste que serão públicos
public_tests=1..num_tests

# Copie todos os arquivos da pasta './files' para a pasta de testes './tests'
cp -r ../files/* ./

for ((i=1; i<=num_tests; i++)); do
    # Nome do arquivo de entrada
    input_file="./in/${i}.in"

    # Nome do arquivo de saída
    output_file="./out/${i}.out"

    # Executa o programa 'prog' com o arquivo de entrada e redireciona a saída para o arquivo de saída
    ../prog.exe < "$input_file" > "$output_file"
done

# Loop de 1 a num_tests para processar os arquivos de entrada
for ((i=1; i<=num_tests; i++)); do
    # Nome do arquivo de entrada
    input_file="./in/${i}.in"

    # Nome do arquivo de saída
    output_file="./out/${i}.out"

    # Verifica se o teste é público ou privado
    if [[ " ${public_tests[*]} " == *" $i "* ]]; then
        # É um teste público, copie para a pasta 'public'
        cp "$input_file" "./public/${i}.in"
        cp "$output_file" "./public/${i}.out"
    else
        # É um teste privado, copie para a pasta 'private'
        cp "$input_file" "./private/${i}.in"
        cp "$output_file" "./private/${i}.out"
    fi
done
