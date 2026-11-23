#ifndef BUSCA_H
#define BUSCA_H

// Busca sequencial: percorre o vetor (nao precisa estar ordenado).
// Retorna o indice da chave ou -1 se nao encontrar.
int buscaSequencial(const int *vetor, int tam, int chave, unsigned long long *comparacoes);

// Busca binaria: exige vetor ordenado em ordem crescente.
// Retorna o indice da chave ou -1 se nao encontrar.
int buscaBinaria(const int *vetor, int tam, int chave, unsigned long long *comparacoes);

#endif
