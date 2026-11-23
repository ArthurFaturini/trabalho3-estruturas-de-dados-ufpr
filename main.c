#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
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

// Le um inteiro do teclado, repetindo a pergunta se o usuario digitar algo invalido
int lerInteiro(const char *mensagem, int minimo)
{
    int valor, c;

    while (1)
    {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1 && valor >= minimo)
            return valor;

        printf("Valor invalido! Digite um numero inteiro");
        if (minimo > 0)
            printf(" maior ou igual a %d", minimo);
        printf(".\n");

        // Descarta o que sobrou da entrada invalida
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        if (c == EOF)
            exit(1);
    }
}

void imprimirVetor(const char *titulo, const int *vetor, int tam)
{
    int i;

    printf("%s: ", titulo);
    for (i = 0; i < tam; i++)
        printf("%d ", vetor[i]);
    printf("\n");
}

void menuBusca(void)
{
    int tam, i, posSeq, posBin;
    int numeros[3];
    int *vetorOriginal, *vetorOrdenado;
    unsigned long long compSeq, compBin, compOrd, permOrd;
    char mensagem[60];

    printf("\n--- BUSCA DE DADOS ---\n");
    tam = lerInteiro("Informe a quantidade de elementos do conjunto de dados: ", 1);

    // 1. Gera o vetor original com numeros aleatorios entre 100 e 100.000
    vetorOriginal = alocarVetor(tam);
    preencherAleatorioIntervalo(vetorOriginal, tam, 100, 100000);

    // 2. Copia o vetor original e ordena a copia (a busca binaria exige vetor ordenado)
    vetorOrdenado = alocarVetor(tam);
    copiarVetor(vetorOriginal, vetorOrdenado, tam);
    shellSort(vetorOrdenado, tam, &compOrd, &permOrd);

    printf("\nVetor com %d elementos gerado (valores entre 100 e 100.000).\n", tam);
    if (tam <= 20)
    {
        imprimirVetor("Vetor original ", vetorOriginal, tam);
        imprimirVetor("Vetor ordenado ", vetorOrdenado, tam);
    }

    // 3. Usuario informa os tres numeros a serem buscados
    printf("\nInforme 3 numeros inteiros para buscar no vetor:\n");
    for (i = 0; i < 3; i++)
    {
        sprintf(mensagem, "Numero %d: ", i + 1);
        numeros[i] = lerInteiro(mensagem, INT_MIN);
    }

    // 4. Busca cada numero pelos dois algoritmos e imprime os resultados
    printf("\n========================================================\n");
    printf("RESULTADO DAS BUSCAS\n");
    printf("========================================================\n");

    for (i = 0; i < 3; i++)
    {
        // Sequencial no vetor original nao ordenado; binaria no vetor ordenado
        posSeq = buscaSequencial(vetorOriginal, tam, numeros[i], &compSeq);
        posBin = buscaBinaria(vetorOrdenado, tam, numeros[i], &compBin);

        printf("\nNumero %d: %d\n", i + 1, numeros[i]);
        if (posSeq >= 0)
            printf("Situacao: encontra-se no conjunto de dados\n");
        else
            printf("Situacao: nao encontra-se no conjunto de dados\n");
        printf("Comparacoes - Busca Sequencial: %llu\n", compSeq);
        printf("Comparacoes - Busca Binaria:    %llu\n", compBin);

        (void)posBin; // os dois algoritmos sempre concordam se o numero existe
    }

    free(vetorOriginal);
    free(vetorOrdenado);
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
            limparTela();
            menuBusca();
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