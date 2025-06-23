#ifndef CONFIGURACOES_H
#define CONFIGURACOES_H

#include <stdbool.h>

typedef struct {
    int pontos_para_vencer;
    int tamanho_baralho;
    bool compra_limitada;
    int tamanho_mao;
} Configuracoes;

void menu_configuracoes(Configuracoes *config);

#endif