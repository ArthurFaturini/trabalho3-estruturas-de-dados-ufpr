#include "ordenacao.h"

void bubbleSort(int *vetor, int tam, unsigned long long *comparacoes, unsigned long long *permutacoes)
{
    int i, j, aux;

    *comparacoes = 0;
    *permutacoes = 0;

    for (i = 0; i < tam - 1; i++)
    {
        for (j = 0; j < tam - 1 - i; j++)
        {
            (*comparacoes)++;
            if (vetor[j] > vetor[j + 1])
            {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
                (*permutacoes)++;
            }
        }
    }
}

void selectionSort(int *vetor, int tam, unsigned long long *comparacoes, unsigned long long *permutacoes)
{
    int i, j, menor, aux;

    *comparacoes = 0;
    *permutacoes = 0;

    for (i = 0; i < tam - 1; i++)
    {
        menor = i;
        for (j = i + 1; j < tam; j++)
        {
            (*comparacoes)++;
            if (vetor[j] < vetor[menor])
            {
                menor = j;
            }
        }
        // Evita contar troca caso o elemento ja esteja na posicao correta
        if (menor != i)
        {
            aux = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = aux;
            (*permutacoes)++;
        }
    }
}

void insertionSort(int *vetor, int tam, unsigned long long *comparacoes, unsigned long long *permutacoes)
{
    int i, j, chave;

    *comparacoes = 0;
    *permutacoes = 0;

    for (i = 1; i < tam; i++)
    {
        chave = vetor[i];
        j = i - 1;

        while (j >= 0)
        {
            (*comparacoes)++;
            if (vetor[j] > chave)
            {
                vetor[j + 1] = vetor[j];
                (*permutacoes)++;
                j--;
            }
            else
            {
                break;
            }
        }
        vetor[j + 1] = chave;
    }
}

void shellSort(int *vetor, int tam, unsigned long long *comparacoes, unsigned long long *permutacoes)
{
    int i, j, h, chave;

    *comparacoes = 0;
    *permutacoes = 0;

    // Define o salto inicial pela sequencia de Knuth (1, 4, 13, 40, 121...)
    h = 1;
    while (h < tam / 3)
    {
        h = 3 * h + 1;
    }

    while (h > 0)
    {
        for (i = h; i < tam; i++)
        {
            chave = vetor[i];
            j = i;

            while (j >= h)
            {
                (*comparacoes)++;
                if (vetor[j - h] > chave)
                {
                    vetor[j] = vetor[j - h];
                    (*permutacoes)++;
                    j -= h;
                }
                else
                {
                    break;
                }
            }
            vetor[j] = chave;
        }
        h = (h - 1) / 3;
    }
}

const char *obterNomeMetodo(int opcaoMetodo)
{
    switch (opcaoMetodo)
    {
    case 1:
        return "BUBBLESORT";
    case 2:
        return "SELECTION SORT";
    case 3:
        return "INSERTION SORT";
    case 4:
        return "SHELL-SORT";
    default:
        return "DESCONHECIDO";
    }
}

void executarOrdenacao(int opcaoMetodo, int *vetor, int tam, unsigned long long *comp, unsigned long long *perm)
{
    switch (opcaoMetodo)
    {
    case 1:
        bubbleSort(vetor, tam, comp, perm);
        break;
    case 2:
        selectionSort(vetor, tam, comp, perm);
        break;
    case 3:
        insertionSort(vetor, tam, comp, perm);
        break;
    case 4:
        shellSort(vetor, tam, comp, perm);
        break;
    }
}