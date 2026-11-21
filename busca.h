#ifndef BUSCA_H
#define BUSCA_H

// Busca sequencial: percorre o vetor do inicio ao fim.
// Retorna o indice da chave ou -1 se nao encontrar.
int buscaSequencial(const int *vetor, int tam, int chave, unsigned long long *comparacoes);

// Busca binaria: exige vetor ordenado em ordem crescente.
// Retorna o indice da chave ou -1 se nao encontrar.
int buscaBinaria(const int *vetor, int tam, int chave, unsigned long long *comparacoes);

// Funcoes auxiliares para selecao e identificacao dos metodos de busca
const char *obterNomeBusca(int opcaoBusca);
int executarBusca(int opcaoBusca, const int *vetor, int tam, int chave, unsigned long long *comp);

// Mede o tempo medio de uma busca repetindo-a ate somar um tempo mensuravel
// (uma unica busca costuma ser rapida demais para o clock()).
double medirTempoBusca(int opcaoBusca, const int *vetor, int tam, int chave);

// Prepara o vetor de teste do metodo escolhido:
//  - Sequencial: dados aleatorios (nao precisa estar ordenado)
//  - Binaria: dados aleatorios ordenados com o Shell-Sort
void prepararVetorBusca(int opcaoBusca, int *vetor, int tam);

#endif
