#ifndef RELATORIO_H
#define RELATORIO_H

#include <stddef.h>

// Executa todos os testes de ordenacao (10 a 1.000.000) e grava no arquivo .txt
void gerarRelatorioOrdenacao(const char *nomeInformado);

// Garante que o nome do arquivo termine com a extensao .txt
void ajustarExtensaoTxt(const char *origem, char *destino, size_t maxTam);

// Retorna o nome formatado do metodo de ordenacao para o relatorio
const char *obterNomeMetodoRelatorio(int metodo);

// Chama a funcao de ordenacao correspondente ao metodo escolhido
void rodarMetodo(int metodo, int *vetor, int tam, unsigned long long *comp, unsigned long long *perm);

#endif