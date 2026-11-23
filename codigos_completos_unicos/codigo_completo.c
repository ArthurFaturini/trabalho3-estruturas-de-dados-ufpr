/*
 * ===========================================================
 *                           NOMES
 *            ARTHUR FATURINI RANGEL DE PAULA ARAUJO
 *            MARCIA KAMILA DE NAZARE FEITOSA RAMOS
 * ===========================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <stddef.h>

/*
================================================================================
                                  vetores.h
================================================================================
*/

#ifndef VETORES_H
#define VETORES_H

// Aloca dinamicamente um vetor de tam inteiros e verifica erro de memoria
int *alocarVetor(int tam);

// Preenche o vetor em ordem crescente (1 a tam)
void preencherOrdenado(int *vetor, int tam);

// Preenche o vetor em ordem decrescente (tam a 1)
void preencherInverso(int *vetor, int tam);

// Preenche o vetor com valores unicos (1 a tam) embaralhados aleatoriamente
void preencherAleatorio(int *vetor, int tam);

// Preenche o vetor com valores aleatorios entre minimo e maximo (podem repetir)
void preencherAleatorioIntervalo(int *vetor, int tam, int minimo, int maximo);

// Copia o conteudo de um vetor para outro de mesmo tamanho
void copiarVetor(const int *origem, int *destino, int tam);

// Gera um numero aleatorio de 32 bits combinando chamadas de rand()
unsigned int gerarAleatorio32(void);

#endif

/*
================================================================================
                                 ordenacao.h
================================================================================
*/

#ifndef ORDENACAO_H
#define ORDENACAO_H

// Prototipos das funcoes de ordenacao
void bubbleSort(int *vetor, int n, unsigned long long *comparacoes, unsigned long long *permutacoes);
void selectionSort(int *vetor, int n, unsigned long long *comparacoes, unsigned long long *permutacoes);
void insertionSort(int *vetor, int n, unsigned long long *comparacoes, unsigned long long *permutacoes);
void shellSort(int *vetor, int n, unsigned long long *comparacoes, unsigned long long *permutacoes);

// Funcoes auxiliares para selecao e identificacao dos metodos
const char *obterNomeMetodo(int opcaoMetodo);
void executarOrdenacao(int opcaoMetodo, int *vetor, int tam, unsigned long long *comp, unsigned long long *perm);

#endif

/*
================================================================================
                                   busca.h
================================================================================
*/

#ifndef BUSCA_H
#define BUSCA_H

// Busca sequencial: percorre o vetor (nao precisa estar ordenado).
// Retorna o indice da chave ou -1 se nao encontrar.
int buscaSequencial(const int *vetor, int tam, int chave, unsigned long long *comparacoes);

// Busca binaria: exige vetor ordenado em ordem crescente.
// Retorna o indice da chave ou -1 se nao encontrar.
int buscaBinaria(const int *vetor, int tam, int chave, unsigned long long *comparacoes);

#endif

/*
================================================================================
                                 relatorio.h
================================================================================
*/

#ifndef RELATORIO_H
#define RELATORIO_H

// Executa todos os testes de ordenacao (10 a 1.000.000) e grava no arquivo .txt
void gerarRelatorioOrdenacao(const char *nomeInformado);

// Garante que o nome do arquivo termine com a extensao .txt
void ajustarExtensaoTxt(const char *origem, char *destino, size_t maxTam);

#endif

/*
================================================================================
                                  vetores.c
================================================================================
*/

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

void preencherAleatorioIntervalo(int *vetor, int tam, int minimo, int maximo)
{
    int i;
    unsigned int amplitude = (unsigned int)(maximo - minimo + 1);

    // Valores aleatorios entre minimo e maximo (inclusive); podem se repetir
    for (i = 0; i < tam; i++)
    {
        vetor[i] = minimo + (int)(gerarAleatorio32() % amplitude);
    }
}

void copiarVetor(const int *origem, int *destino, int tam)
{
    memcpy(destino, origem, (size_t)tam * sizeof(int));
}

/*
================================================================================
                                 ordenacao.c
================================================================================
*/

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

/*
================================================================================
                                   busca.c
================================================================================
*/

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

/*
================================================================================
                                 relatorio.c
================================================================================
*/

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

/*
================================================================================
                                    main.c
================================================================================
*/

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
