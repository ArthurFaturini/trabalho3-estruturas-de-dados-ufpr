#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetores.h"

// Combina chamadas de rand() para gerar um numero de 32 bits,
// superando o limite de RAND_MAX (32767) no Windows
unsigned int gerarAleatorio32(void)
{
    unsigned int r1, r2, r3;

    r1 = (unsigned int)(rand() & 0x7FFF);
    r2 = (unsigned int)(rand() & 0x7FFF);
    r3 = (unsigned int)(rand() & 0x0003);

    return (r1 << 17) | (r2 << 2) | r3;
}

int *alocarVetor(int tam)
{
    int *vetor;

    vetor = (int *)malloc((size_t)tam * sizeof(int));
    if (vetor == NULL)
    {
        printf("Erro critico: falha ao alocar memoria para %d elementos.\n", tam);
        exit(1);
    }

    return vetor;
}

void preencherOrdenado(int *vetor, int tam)
{
    int i;

    for (i = 0; i < tam; i++)
    {
        vetor[i] = i + 1;
    }
}

void preencherInverso(int *vetor, int tam)
{
    int i;

    for (i = 0; i < tam; i++)
    {
        vetor[i] = tam - i;
    }
}

void preencherAleatorio(int *vetor, int tam)
{
    int i, j, aux;

    // 1. Preenche com inteiros unicos de 1 ate n
    for (i = 0; i < tam; i++)
    {
        vetor[i] = i + 1;
    }

    // 2. Embaralhamento de Fisher-Yates
    for (i = tam - 1; i > 0; i--)
    {
        j = (int)(gerarAleatorio32() % (unsigned int)(i + 1));
        aux = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = aux;
    }
}

void copiarVetor(const int *origem, int *destino, int tam)
{
    memcpy(destino, origem, (size_t)tam * sizeof(int));
}