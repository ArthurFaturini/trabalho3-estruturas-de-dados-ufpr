#include "busca.h"

int buscaSequencial(const int *vetor, int tam, int chave, unsigned long long *comparacoes)
{
    int i;

    *comparacoes = 0;

    for (i = 0; i < tam; i++)
    {
        (*comparacoes)++;
        if (vetor[i] == chave)
        {
            return i;
        }
    }

    return -1;
}

int buscaBinaria(const int *vetor, int tam, int chave, unsigned long long *comparacoes)
{
    int inicio, fim, meio;

    *comparacoes = 0;
    inicio = 0;
    fim = tam - 1;

    while (inicio <= fim)
    {
        meio = inicio + (fim - inicio) / 2; // evita overflow de (inicio + fim)

        (*comparacoes)++;
        if (vetor[meio] == chave)
        {
            return meio;
        }

        (*comparacoes)++;
        if (chave < vetor[meio])
        {
            fim = meio - 1;
        }
        else
        {
            inicio = meio + 1;
        }
    }

    return -1;
}
