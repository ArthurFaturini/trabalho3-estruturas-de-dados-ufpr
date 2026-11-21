#ifndef RELATORIO_H
#define RELATORIO_H

#include <stddef.h>

// Executa todos os testes de ordenacao (10 a 1.000.000) e grava no arquivo .txt
void gerarRelatorioOrdenacao(const char *nomeInformado);

// Executa os testes de busca sequencial e binaria (10 a 1.000.000) e grava no arquivo .txt
void gerarRelatorioBusca(const char *nomeInformado);

// Garante que o nome do arquivo termine com a extensao .txt
void ajustarExtensaoTxt(const char *origem, char *destino, size_t maxTam);

#endif