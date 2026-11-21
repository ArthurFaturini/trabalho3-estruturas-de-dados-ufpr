#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ordenacao.h"
#include "vetores.h"
#include "relatorio.h"
#include "busca.h"

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

void imprimirResultadoBusca(const char *descricao, int chave, int posicao,
                            unsigned long long comparacoes, double tempo)
{
    printf("\n%s (chave = %d)\n", descricao, chave);
    if (posicao >= 0)
        printf("Resultado: encontrado na posicao %d\n", posicao);
    else
        printf("Resultado: nao encontrado\n");
    printf("Quantidade de Comparacoes: %llu\n", comparacoes);
    printf("Tempo medio da busca: %.9f segundos\n", tempo);
}

void testarBuscaPorTamanho(int opcaoBusca, int tam)
{
    int *vetor;
    int chaves[4], posicao, i, chaveUsuario;
    unsigned long long comparacoes;
    double tempo;
    const char *descricoes[4] = {
        "Chave na primeira posicao do vetor",
        "Chave no meio do vetor",
        "Chave na ultima posicao do vetor",
        "Chave inexistente no vetor"};

    vetor = alocarVetor(tam);
    prepararVetorBusca(opcaoBusca, vetor, tam);

    printf("\n========================================================\n");
    printf("Metodo de busca: %s\n", obterNomeBusca(opcaoBusca));
    printf("Conjunto com %d elementos (%s)\n", tam,
           opcaoBusca == 2 ? "aleatorios, ordenados com Shell-Sort" : "aleatorios");
    printf("========================================================\n");

    chaves[0] = vetor[0];
    chaves[1] = vetor[(tam - 1) / 2];
    chaves[2] = vetor[tam - 1];
    chaves[3] = tam + 1; // os valores vao de 1 a tam, entao tam+1 nao existe

    for (i = 0; i < 4; i++)
    {
        posicao = executarBusca(opcaoBusca, vetor, tam, chaves[i], &comparacoes);
        tempo = medirTempoBusca(opcaoBusca, vetor, tam, chaves[i]);
        imprimirResultadoBusca(descricoes[i], chaves[i], posicao, comparacoes, tempo);
    }

    printf("\nInforme um valor para buscar (1 a %d) ou 0 para pular: ", tam);
    if (scanf("%d", &chaveUsuario) == 1 && chaveUsuario != 0)
    {
        posicao = executarBusca(opcaoBusca, vetor, tam, chaveUsuario, &comparacoes);
        tempo = medirTempoBusca(opcaoBusca, vetor, tam, chaveUsuario);
        imprimirResultadoBusca("Chave informada pelo usuario", chaveUsuario, posicao, comparacoes, tempo);
    }

    free(vetor);
}

void menuBusca(void)
{
    int opcaoBusca, tam;

    do
    {
        printf("\n--- METODOS DE BUSCA ---\n");
        printf("1 - Busca Sequencial\n");
        printf("2 - Busca Binaria\n");
        printf("0 - Voltar ao menu principal\n");
        printf("Escolha o metodo: ");
        scanf("%d", &opcaoBusca);

        if (opcaoBusca == 0)
        {
            limparTela();
            break;
        }

        if (opcaoBusca < 1 || opcaoBusca > 2)
        {
            printf("Metodo invalido!\n");
            pausarTela();
            continue;
        }

        tam = selecionarTamanho();
        if (tam > 0)
        {
            testarBuscaPorTamanho(opcaoBusca, tam);
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

    } while (opcaoBusca != 0);
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
        printf("4 - Gerar arquivo .txt de Busca\n");
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
            limparTela();
            menuBusca();
            break;
        case 3:
            printf("\nInforme o nome do arquivo de saida (ex: resultados.txt): ");
            scanf(" %249[^\n]", nomeArquivo);
            gerarRelatorioOrdenacao(nomeArquivo);
            pausarTela();
            break;
        case 4:
            printf("\nInforme o nome do arquivo de saida (ex: busca.txt): ");
            scanf(" %249[^\n]", nomeArquivo);
            gerarRelatorioBusca(nomeArquivo);
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