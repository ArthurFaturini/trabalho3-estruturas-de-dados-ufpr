#ifndef ORDENACAO_H
#define ORDENACAO_H

// Prototipos das funcoes de ordenacao
void bubbleSort(int *vetor, int n, unsigned long long *comparacoes, unsigned long long *permutacoes);
void selectionSort(int *vetor, int n, unsigned long long *comparacoes, unsigned long long *permutacoes);
void insertionSort(int *vetor, int n, unsigned long long *comparacoes, unsigned long long *permutacoes);
void shellSort(int *vetor, int n, unsigned long long *comparacoes, unsigned long long *permutacoes);

// Funcoes auxiliares para selecao e identificacao dos metodos
const char *obterNomeMetodo(int opcaoMetodo);
void executarOrdenacao(int opcaoMetodo, int *vetor, int tam, unsigned long long *comp, unsigned long long *perm);

#endif