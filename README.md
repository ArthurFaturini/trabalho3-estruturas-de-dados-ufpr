# Trabalho 3 – Ordenação e Busca

Programa em C que compara métodos de **ordenação** e de **busca**, medindo
quantidade de comparações, permutações e tempo de execução para conjuntos de
10 a 1.000.000 elementos.

## Estrutura

| Arquivo | Conteúdo |
|---|---|
| `main.c` | Menus e testes interativos de ordenação e busca |
| `ordenacao.c/.h` | Bubble Sort, Selection Sort, Insertion Sort e Shell-Sort (sequência de Knuth) |
| `busca.c/.h` | Busca Sequencial e Busca Binária, medição de tempo e preparação dos vetores |
| `vetores.c/.h` | Alocação e preenchimento de vetores (ordenado, inverso e aleatório) |
| `relatorio.c/.h` | Geração dos relatórios `.txt` de ordenação e de busca |

## Como compilar e executar

```bash
gcc -Wall -O2 -std=c99 *.c -o trabalho3
./trabalho3          # Linux/macOS
trabalho3.exe        # Windows
```

## Menu principal

1. **Ordenação de Dados** – escolhe o método e o tamanho; ordena o vetor nos
   três cenários: inicialmente ordenado, ordenado inversamente e aleatório.
2. **Busca de Dados** – escolhe Busca Sequencial ou Binária e o tamanho; testa
   chave na primeira posição, no meio, na última posição e uma chave
   inexistente. No final, permite buscar um valor digitado pelo usuário.
3. **Gerar arquivo .txt de Ordenação** – roda os 4 métodos em todos os tamanhos.
4. **Gerar arquivo .txt de Busca** – roda os 2 métodos de busca em todos os tamanhos.

## Decisões de implementação

- **Dados aleatórios sem repetição:** o vetor recebe os valores de 1 a *n* e é
  embaralhado com Fisher–Yates. Como `RAND_MAX` vale 32767 no Windows, três
  chamadas de `rand()` são combinadas para gerar números de 32 bits.
- **Mesma semente nos relatórios:** todos os métodos ordenam/buscam exatamente
  os mesmos dados aleatórios em cada tamanho, para a comparação ser justa.
- **Permutações:** no Bubble e no Selection conta-se cada troca; no Insertion e
  no Shell conta-se cada deslocamento de elemento.
- **Busca Binária:** exige vetor ordenado, por isso o vetor aleatório é
  ordenado com o Shell-Sort antes da busca. Cada iteração conta até 2
  comparações (igualdade e menor/maior).
- **Tempo da busca:** uma única busca é rápida demais para o `clock()`. A busca
  é repetida em lotes até somar ~0,05 s, e o tempo informado é a média por busca.

## Complexidade esperada

| Método | Melhor caso | Caso médio | Pior caso |
|---|---|---|---|
| Bubble Sort | O(n²)* | O(n²) | O(n²) |
| Selection Sort | O(n²) | O(n²) | O(n²) |
| Insertion Sort | O(n) | O(n²) | O(n²) |
| Shell-Sort (Knuth) | O(n log n) | ≈ O(n^1,25) | O(n^1,5) |
| Busca Sequencial | O(1) | O(n) | O(n) |
| Busca Binária | O(1) | O(log n) | O(log n) |

\* Sem a otimização de parada antecipada (flag de troca), o Bubble Sort faz
n(n−1)/2 comparações mesmo com o vetor já ordenado.

## Observação sobre tempo de execução

Os métodos O(n²) com 1.000.000 de elementos fazem cerca de 5 × 10¹¹
comparações por cenário, então o relatório completo de ordenação pode levar
**várias horas**. A busca completa leva poucos segundos.
