#ifndef CARTAS_H
#define CARTAS_H

typedef enum {
    PEDRA,
    PAPEL,
    TESOURA
} TipoCarta;

typedef struct Carta {
    TipoCarta tipo;
    struct Carta *proximo;
} Carta;

const char* tipo_para_string(TipoCarta tipo);

void adicionar_carta_inicio(Carta **lista, TipoCarta tipo);
Carta* criar_baralho(int tamanho_total);
void embaralhar(Carta **lista);
Carta* remover_carta_por_posicao(Carta **lista, int pos);
void comprar_carta(Carta **baralho, Carta **mao);
int contar_cartas(Carta *lista);
void liberar_lista(Carta **lista);
void exibir_mao_formatada(Carta *mao);

#endif