#include <stdio.h>
#include <locale.h>
#include "placar.h"
#include "utils.h"

#define NOME_ARQUIVO "placar.txt"

void ler_placar(int *vitorias, int *derrotas) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "r");
    if (arquivo == NULL) {
        *vitorias = 0;
        *derrotas = 0;
        return;
    }
    
    if (fscanf(arquivo, "Vitorias: %d / Derrotas: %d", vitorias, derrotas) != 2) {
        rewind(arquivo);
        if (fscanf(arquivo, "%d %d", vitorias, derrotas) != 2) {
            *vitorias = 0;
            *derrotas = 0;
        }
    }
    fclose(arquivo);
}

void salvar_placar(int vitorias, int derrotas) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar o placar!\n");
        return;
    }
    fprintf(arquivo, "Vitorias: %d / Derrotas: %d", vitorias, derrotas);
    fclose(arquivo);
}

void exibir_winrate() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int vitorias, derrotas;
    ler_placar(&vitorias, &derrotas);
        limpar_tela();
    printf("\n--- PONTUAÇÃO GERAL ---\n");
    printf("Vitórias/Derrotas: %d/%d\n", vitorias, derrotas);
    printf("-----------------------\n");
        pausar_tela(3000);
        limpar_tela();
}
