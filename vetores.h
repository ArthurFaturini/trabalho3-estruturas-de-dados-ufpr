#ifndef VETORES_H
#define VETORES_H

// Aloca dinamicamente um vetor de tam inteiros e verifica erro de memoria
int *alocarVetor(int tam);

// Preenche o vetor em ordem crescente (1 a tam)
void preencherOrdenado(int *vetor, int tam);

// Preenche o vetor em ordem decrescente (tam a 1)
void preencherInverso(int *vetor, int tam);

// Preenche o vetor com valores unicos (1 a tam) embaralhados aleatoriamente
void preencherAleatorio(int *vetor, int tam);

// Copia o conteudo de um vetor para outro de mesmo tamanho
void copiarVetor(const int *origem, int *destino, int tam);

// Gera um numero aleatorio de 32 bits combinando chamadas de rand()
unsigned int gerarAleatorio32(void);

#endif