#include <time.h>
#include "busca.h"
#include "ordenacao.h"
#include "vetores.h"

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

const char *obterNomeBusca(int opcaoBusca)
{
    switch (opcaoBusca)
    {
    case 1:
        return "BUSCA SEQUENCIAL";
    case 2:
        return "BUSCA BINARIA";
    default:
        return "DESCONHECIDO";
    }
}

int executarBusca(int opcaoBusca, const int *vetor, int tam, int chave, unsigned long long *comp)
{
    switch (opcaoBusca)
    {
    case 1:
        return buscaSequencial(vetor, tam, chave, comp);
    case 2:
        return buscaBinaria(vetor, tam, chave, comp);
    default:
        *comp = 0;
        return -1;
    }
}

double medirTempoBusca(int opcaoBusca, const int *vetor, int tam, int chave)
{
    clock_t inicio, decorrido;
    unsigned long long comp;
    volatile int resultado; // impede o compilador de descartar as buscas
    long repeticoes = 1, r;
    const clock_t tempoMinimo = CLOCKS_PER_SEC / 20; // ~0,05 s de medicao

    // Dobra o numero de repeticoes ate o lote durar um tempo mensuravel.
    // O clock() so e chamado no inicio e no fim de cada lote, para que o
    // custo do proprio relogio nao contamine a medicao.
    for (;;)
    {
        inicio = clock();
        for (r = 0; r < repeticoes; r++)
        {
            resultado = executarBusca(opcaoBusca, vetor, tam, chave, &comp);
        }
        decorrido = clock() - inicio;

        if (decorrido >= tempoMinimo || repeticoes >= (1L << 26))
            break;
        repeticoes *= 2;
    }
    (void)resultado;

    return ((double)decorrido / CLOCKS_PER_SEC) / (double)repeticoes;
}

void prepararVetorBusca(int opcaoBusca, int *vetor, int tam)
{
    unsigned long long comp, perm;

    preencherAleatorio(vetor, tam);

    if (opcaoBusca == 2)
    {
        // A busca binaria so funciona com o vetor ordenado
        shellSort(vetor, tam, &comp, &perm);
    }
}
