#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "relatorio.h"
#include "ordenacao.h"
#include "vetores.h"

void ajustarExtensaoTxt(const char *origem, char *destino, size_t maxTam)
{
    size_t len;

    strncpy(destino, origem, maxTam - 5);
    destino[maxTam - 5] = '\0';
    len = strlen(destino);

    // Adiciona ".txt" caso o usuario nao tenha digitado a extensao
    if (len < 4 || strcmp(destino + len - 4, ".txt") != 0)
    {
        strcat(destino, ".txt");
    }
}

void gerarRelatorioOrdenacao(const char *nomeInformado)
{
    FILE *arquivo;
    char nomeArquivo[260];
    int tamanhos[6] = {10, 100, 1000, 10000, 100000, 1000000};
    int m, t, tam;
    int *vetor;
    unsigned long long comparacoes, permutacoes;
    clock_t inicio, fim;
    double tempoGasto;
    const char *nomeMetodo;
    unsigned int sementeBase;

    ajustarExtensaoTxt(nomeInformado, nomeArquivo, sizeof(nomeArquivo));

    arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao criar o arquivo '%s'.\n", nomeArquivo);
        return;
    }

    printf("\nIniciando geracao do relatorio em '%s'...\n", nomeArquivo);

    // Mesma semente base para que todos os 4 metodos ordenem exatamente
    // os mesmos vetores aleatorios em cada tamanho, sem precisar manter
    // multiplos vetores alocados simultaneamente.
    sementeBase = (unsigned int)time(NULL);

    for (m = 1; m <= 4; m++)
    {
        srand(sementeBase);
        nomeMetodo = obterNomeMetodo(m);

        // Separador visual para cada metodo de ordenacao
        fprintf(arquivo, "========================================================\n");
        fprintf(arquivo, "Metodo de ordenacao: %s\n", nomeMetodo);
        fprintf(arquivo, "========================================================\n\n");

        for (t = 0; t < 6; t++)
        {
            tam = tamanhos[t];
            printf("Processando %s - %d elementos...\n", nomeMetodo, tam);
            fflush(stdout);

            // Separador visual a cada aumento de tamanho do vetor
            fprintf(arquivo, "--------------------------------------------------------\n");
            fprintf(arquivo, ">>> TAMANHO DO CONJUNTO: %d ELEMENTOS <<<\n", tam);
            fprintf(arquivo, "--------------------------------------------------------\n");

            vetor = alocarVetor(tam);

            // 1. Inicialmente ordenado
            preencherOrdenado(vetor, tam);
            inicio = clock();
            executarOrdenacao(m, vetor, tam, &comparacoes, &permutacoes);
            fim = clock();
            tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

            fprintf(arquivo, "Conjunto com %d elementos - inicialmente ordenado\n", tam);
            fprintf(arquivo, "Quantidade de Comparacoes: %llu\n", comparacoes);
            fprintf(arquivo, "Quantidades de Permutacoes: %llu\n", permutacoes);
            fprintf(arquivo, "Tempo gasto para ordenacao: %.6f segundos\n\n", tempoGasto);

            // 2. Inicialmente ordenado inversamente
            preencherInverso(vetor, tam);
            inicio = clock();
            executarOrdenacao(m, vetor, tam, &comparacoes, &permutacoes);
            fim = clock();
            tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

            fprintf(arquivo, "Conjunto com %d elementos - inicialmente ordenado inversamente\n", tam);
            fprintf(arquivo, "Quantidade de Comparacoes: %llu\n", comparacoes);
            fprintf(arquivo, "Quantidades de Permutacoes: %llu\n", permutacoes);
            fprintf(arquivo, "Tempo gasto para ordenacao: %.6f segundos\n\n", tempoGasto);

            // 3. Dados posicionados de forma aleatoria
            preencherAleatorio(vetor, tam);
            inicio = clock();
            executarOrdenacao(m, vetor, tam, &comparacoes, &permutacoes);
            fim = clock();
            tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

            fprintf(arquivo, "Conjunto com %d elementos - com dados posicionados de forma aleatoria\n", tam);
            fprintf(arquivo, "Quantidade de Comparacoes: %llu\n", comparacoes);
            fprintf(arquivo, "Quantidades de Permutacoes: %llu\n", permutacoes);
            fprintf(arquivo, "Tempo gasto para ordenacao: %.6f segundos\n\n", tempoGasto);

            fflush(arquivo);
            free(vetor);
        }
    }

    fclose(arquivo);
    printf("\nRelatorio concluido com sucesso! Arquivo salvo como: %s\n", nomeArquivo);
}