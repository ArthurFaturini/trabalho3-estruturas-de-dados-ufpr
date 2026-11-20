#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ordenacao.h"
#include "vetores.h"
#include "relatorio.h"

void limparTela(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausarTela(void)
{
    int c;

    // Limpa o '\n' residual deixado pelo ultimo scanf no buffer de entrada
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    printf("\nPressione ENTER para continuar...");
    fflush(stdout);

    // Aguarda o usuario pressionar ENTER (e descarta qualquer caractere extra digitado)
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    limparTela();
}

int selecionarTamanho(void)
{
    int opcao;

    printf("\n--- SELECIONE O TAMANHO DO CONJUNTO ---\n");
    printf("1 - 10 elementos\n");
    printf("2 - 100 elementos\n");
    printf("3 - 1.000 elementos\n");
    printf("4 - 10.000 elementos\n");
    printf("5 - 100.000 elementos\n");
    printf("6 - 1.000.000 elementos\n");
    printf("0 - Voltar\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        return 10;
    case 2:
        return 100;
    case 3:
        return 1000;
    case 4:
        return 10000;
    case 5:
        return 100000;
    case 6:
        return 1000000;
    case 0:
        return 0;
    default:
        printf("Opcao de tamanho invalida!\n");
        return -1;
    }
}

void testarOrdenacaoPorTamanho(int opcaoMetodo, int tam)
{
    int *vetor;
    unsigned long long comparacoes, permutacoes;
    clock_t inicio, fim;
    double tempoGasto;

    vetor = alocarVetor(tam);

    printf("\n========================================================\n");
    printf("Metodo de ordenacao: %s\n", obterNomeMetodo(opcaoMetodo));
    printf("========================================================\n");

    // 1. Inicialmente ordenado
    preencherOrdenado(vetor, tam);
    inicio = clock();
    executarOrdenacao(opcaoMetodo, vetor, tam, &comparacoes, &permutacoes);
    fim = clock();
    tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nConjunto com %d elementos - inicialmente ordenado\n", tam);
    printf("Quantidade de Comparacoes: %llu\n", comparacoes);
    printf("Quantidades de Permutacoes: %llu\n", permutacoes);
    printf("Tempo gasto para ordenacao: %.6f segundos\n", tempoGasto);

    // 2. Inicialmente ordenado inversamente
    preencherInverso(vetor, tam);
    inicio = clock();
    executarOrdenacao(opcaoMetodo, vetor, tam, &comparacoes, &permutacoes);
    fim = clock();
    tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nConjunto com %d elementos - inicialmente ordenado inversamente\n", tam);
    printf("Quantidade de Comparacoes: %llu\n", comparacoes);
    printf("Quantidades de Permutacoes: %llu\n", permutacoes);
    printf("Tempo gasto para ordenacao: %.6f segundos\n", tempoGasto);

    // 3. Dados posicionados de forma aleatoria
    preencherAleatorio(vetor, tam);
    inicio = clock();
    executarOrdenacao(opcaoMetodo, vetor, tam, &comparacoes, &permutacoes);
    fim = clock();
    tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nConjunto com %d elementos - com dados posicionados de forma aleatoria\n", tam);
    printf("Quantidade de Comparacoes: %llu\n", comparacoes);
    printf("Quantidades de Permutacoes: %llu\n", permutacoes);
    printf("Tempo gasto para ordenacao: %.6f segundos\n", tempoGasto);

    free(vetor);
}

void menuOrdenacao(void)
{
    int opcaoMetodo, tam;

    do
    {
        printf("\n--- METODOS DE ORDENACAO ---\n");
        printf("1 - Bubble Sort\n");
        printf("2 - Selection Sort\n");
        printf("3 - Insertion Sort\n");
        printf("4 - Shell-Sort\n");
        printf("0 - Voltar ao menu principal\n");
        printf("Escolha o metodo: ");
        scanf("%d", &opcaoMetodo);

        if (opcaoMetodo == 0)
        {
            limparTela();
            break;
        }

        if (opcaoMetodo < 1 || opcaoMetodo > 4)
        {
            printf("Metodo invalido!\n");
            pausarTela();
            continue;
        }

        tam = selecionarTamanho();
        if (tam > 0)
        {
            testarOrdenacaoPorTamanho(opcaoMetodo, tam);
            pausarTela();
        }
        else if (tam == 0)
        {
            limparTela();
        }
        else
        {
            pausarTela();
        }

    } while (opcaoMetodo != 0);
}

int main(void)
{
    int opcaoPrincipal;
    char nomeArquivo[250];

    srand((unsigned int)time(NULL));

    do
    {
        printf("\n=== TRABALHO 3 - ORDENACAO E BUSCA ===\n");
        printf("1 - Ordenacao de Dados (Teste interativo)\n");
        printf("2 - Busca de Dados\n");
        printf("3 - Gerar arquivo .txt de Ordenacao\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcaoPrincipal);

        switch (opcaoPrincipal)
        {
        case 1:
            limparTela();
            menuOrdenacao();
            break;
        case 2:
            printf("\n[Modulo de Busca aguardando integracao]\n");
            pausarTela();
            break;
        case 3:
            printf("\nInforme o nome do arquivo de saida (ex: resultados.txt): ");
            scanf(" %249[^\n]", nomeArquivo);
            gerarRelatorioOrdenacao(nomeArquivo);
            pausarTela();
            break;
        case 0:
            printf("\nEncerrando programa...\n");
            break;
        default:
            printf("\nOpcao invalida!\n");
            pausarTela();
            break;
        }

    } while (opcaoPrincipal != 0);

    return 0;
}