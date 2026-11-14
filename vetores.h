#ifndef VETORES_H
#define VETORES_H

// Aloca dinamicamente um vetor de n inteiros e verifica erro de memoria
int *alocarVetor(int tam);

// Preenche o vetor em ordem crescente (1 a n)
void preencherOrdenado(int *vetor, int tam);

// Preenche o vetor em ordem decrescente (n a 1)
void preencherInverso(int *vetor, int tam);

// Preenche o vetor com valores unicos (1 a n) embaralhados aleatoriamente
void preencherAleatorio(int *vetor, int tam);

// Copia o conteudo de um vetor para outro de mesmo tamanho
void copiarVetor(const int *origem, int *destino, int tam);

#endif