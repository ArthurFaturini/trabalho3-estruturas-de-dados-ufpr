# Trabalho 3 – Ordenação e Busca

Programa em C que compara métodos de **ordenação** (comparações, permutações e
tempo para conjuntos de 10 a 1.000.000 elementos) e de **busca** (comparações
da Pesquisa Sequencial e da Pesquisa Binária).

## Estrutura

| Arquivo | Conteúdo |
|---|---|
| `main.c` | Menus e testes interativos de ordenação e busca |
| `ordenacao.c/.h` | Bubble Sort, Selection Sort, Insertion Sort e Shell-Sort (sequência de Knuth) |
| `busca.c/.h` | Busca Sequencial e Busca Binária, com contagem de comparações |
| `vetores.c/.h` | Alocação, cópia e preenchimento de vetores (ordenado, inverso, aleatório sem repetição e aleatório entre 100 e 100.000) |
| `relatorio.c/.h` | Geração do relatório `.txt` de ordenação |

## Como compilar e executar

```bash
gcc -Wall -O2 -std=c99 *.c -o trabalho3
./trabalho3          # Linux/macOS
trabalho3.exe        # Windows
```

## Menu principal

1. **Ordenação de Dados** – escolhe o método e o tamanho; ordena o vetor nos
   três cenários: inicialmente ordenado, ordenado inversamente e aleatório.
2. **Busca de Dados** – o usuário informa a quantidade de elementos; o programa
   gera números aleatórios entre 100 e 100.000, e o usuário informa 3 números
   inteiros. Cada número é buscado pelos dois algoritmos, e o programa mostra se
   ele se encontra ou não no conjunto e quantas comparações cada busca fez.
3. **Gerar arquivo .txt de Ordenação** – roda os 4 métodos em todos os tamanhos
   e grava no arquivo com o nome informado.

## Decisões de implementação

- **Dados aleatórios sem repetição:** o vetor recebe os valores de 1 a *n* e é
  embaralhado com Fisher–Yates. Como `RAND_MAX` vale 32767 no Windows, três
  chamadas de `rand()` são combinadas para gerar números de 32 bits.
- **Mesma semente nos relatórios:** todos os métodos ordenam exatamente
  os mesmos dados aleatórios em cada tamanho, para a comparação ser justa.
- **Permutações:** no Bubble e no Selection conta-se cada troca; no Insertion e
  no Shell conta-se cada deslocamento de elemento.
- **Busca:** a Pesquisa Sequencial é feita no vetor original (não ordenado). A
  Pesquisa Binária é feita numa cópia do vetor original ordenada com o
  Shell-Sort. Na busca os números podem se repetir, já que o enunciado só define
  o intervalo (100 a 100.000).
- **Comparações da Busca Binária:** cada iteração conta até 2 comparações
  (se é igual à chave e, se não for, se é menor ou maior).

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
**várias horas**. 