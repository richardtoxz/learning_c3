#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cartas.h"

const char* tipo_para_string(TipoCarta tipo) {
    switch (tipo) {
        case PEDRA:   return "Pedra";
        case PAPEL:   return "Papel";
        case TESOURA: return "Tesoura";
        default:      return "Desconhecido";
    }
}

void adicionar_carta_inicio(Carta **lista, TipoCarta tipo) {
    Carta *nova_carta = (Carta*) malloc(sizeof(Carta));
    nova_carta->tipo = tipo;
    nova_carta->proximo = *lista;
    *lista = nova_carta;
}

Carta* criar_baralho(int tamanho_total) {
    Carta *baralho = NULL;
    int cartas_por_tipo = tamanho_total / 3;
    for (int i = 0; i < cartas_por_tipo; i++) {
        adicionar_carta_inicio(&baralho, PEDRA);
        adicionar_carta_inicio(&baralho, PAPEL);
        adicionar_carta_inicio(&baralho, TESOURA);
    }
    return baralho;
}

void embaralhar(Carta **lista) {
    int n = contar_cartas(*lista);
    if (n > 1) {
        Carta **array_de_ponteiros = (Carta**) malloc(n * sizeof(Carta*));
        Carta *atual = *lista;
        for (int i = 0; i < n; i++) {
            array_de_ponteiros[i] = atual;
            atual = atual->proximo;
        }

        for (int i = 0; i < n - 1; i++) {
            int j = i + rand() / (RAND_MAX / (n - i) + 1);
            Carta *temp = array_de_ponteiros[j];
            array_de_ponteiros[j] = array_de_ponteiros[i];
            array_de_ponteiros[i] = temp;
        }

        *lista = array_de_ponteiros[0];
        for (int i = 0; i < n - 1; i++) {
            array_de_ponteiros[i]->proximo = array_de_ponteiros[i + 1];
        }
        array_de_ponteiros[n - 1]->proximo = NULL;

        free(array_de_ponteiros);
    }
}

Carta* remover_carta_por_posicao(Carta **lista, int pos) {
    if (*lista == NULL || pos < 1) return NULL;

    Carta *atual = *lista;
    Carta *anterior = NULL;
    int i = 1;

    while (atual != NULL && i < pos) {
        anterior = atual;
        atual = atual->proximo;
        i++;
    }
    
    if (atual == NULL) return NULL;

    if (anterior == NULL) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    
    atual->proximo = NULL;
    return atual;
}

void comprar_carta(Carta **baralho, Carta **mao) {
    if (*baralho == NULL) return;
    Carta* carta_comprada = remover_carta_por_posicao(baralho, 1);
    if (carta_comprada != NULL) {
        carta_comprada->proximo = *mao;
        *mao = carta_comprada;
    }
}

int contar_cartas(Carta *lista) {
    int count = 0;
    Carta *atual = lista;
    while (atual != NULL) {
        count++;
        atual = atual->proximo;
    }
    return count;
}

void liberar_lista(Carta **lista) {
    Carta *atual = *lista;
    Carta *proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *lista = NULL;
}

void exibir_mao_formatada(Carta *mao) {
    Carta *atual = mao;
    int i = 1;
    char sigla;
    while (atual != NULL) {
        switch(atual->tipo) {
            case PEDRA: sigla = 'D'; break;
            case PAPEL: sigla = 'P'; break;
            case TESOURA: sigla = 'T'; break;
        }
        printf("%c%d ", sigla, i);
        atual = atual->proximo;
        i++;
    }
    printf("\n");
}