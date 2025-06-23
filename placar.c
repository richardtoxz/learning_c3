#include <stdio.h>
#include "placar.h"

#define NOME_ARQUIVO "placar.txt"

void ler_placar(int *vitorias, int *derrotas) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "r");
    if (arquivo == NULL) {
        *vitorias = 0;
        *derrotas = 0;
        return;
    }
    fscanf(arquivo, "%d %d", vitorias, derrotas);
    fclose(arquivo);
}

void salvar_placar(int vitorias, int derrotas) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar o placar!\n");
        return;
    }
    fprintf(arquivo, "%d %d", vitorias, derrotas);
    fclose(arquivo);
}

void exibir_winrate() {
    int vitorias, derrotas;
    ler_placar(&vitorias, &derrotas);
    printf("\n--- PONTUAÇÃO GERAL ---\n");
    printf("Vitórias/Derrotas: %d/%d\n", vitorias, derrotas);
    printf("-----------------------\n");
}