#!/bin/bash

CC=tcc
NAME=main

# Compilar todos os arquivos .c em arquivos objeto .o
for file in *.c; do
  echo $CC -c $file -o ${file%.c}.o
  $CC -c $file -o ${file%.c}.o
done

# Juntar todos os arquivos objeto em um executável
echo $CC *.o -o $NAME
$CC *.o -o $NAME

# Remover os arquivos objeto após a criação do executável
echo rm *.o
rm *.o
