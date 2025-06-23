#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "jogo.h"
#include "cartas.h"
#include "placar.h"
#include "utils.h"

typedef enum { VITORIA, DERROTA, EMPATE } ResultadoRodada;

typedef struct {
    char nome[20];
    int pontos_rodada;
    Carta *mao;
} Jogador;

ResultadoRodada comparar_cartas(TipoCarta j1, TipoCarta cpu) {
    if (j1 == cpu) return EMPATE;
    if ((j1 == PEDRA && cpu == TESOURA) ||
        (j1 == TESOURA && cpu == PAPEL) ||
        (j1 == PAPEL && cpu == PEDRA)) {
        return VITORIA;
    }
    return DERROTA;
}

void iniciar_partida(Configuracoes config) {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Jogador jogador1 = {"Jogador", 0, NULL};
    Jogador cpu = {"CPU", 0, NULL};
    Carta *baralho = criar_baralho(config.tamanho_baralho);
    Carta *descarte = NULL;

    if (baralho == NULL) {
        printf("Erro: Não foi possível criar o baralho!\n");
        return;
    }

    embaralhar(&baralho);

    for (int i = 0; i < config.tamanho_mao; i++) {
        comprar_carta(&baralho, &jogador1.mao);
        comprar_carta(&baralho, &cpu.mao);
    }
    
    int rodada_atual = 1;
    while (jogador1.pontos_rodada < config.pontos_para_vencer && cpu.pontos_rodada < config.pontos_para_vencer) {
        limpar_tela();
        printf("\n================================================\n");
        printf("Rodada %d - Placar: Jogador %d x %d CPU\n", rodada_atual, jogador1.pontos_rodada, cpu.pontos_rodada);
        printf("------------------------------------------------\n");
          printf("Sua mão: ");
        exibir_mao_formatada(jogador1.mao);
        
        int num_cartas_mao = contar_cartas(jogador1.mao);
        if (num_cartas_mao == 0) {
            printf("Erro: Jogador ficou sem cartas!\n");
            break;
        }
        
        char prompt[100];
        snprintf(prompt, sizeof(prompt), "Escolha uma carta para jogar (1 a %d): ", num_cartas_mao);
        int escolha_jogador_pos = ler_inteiro_seguro(prompt, 1, num_cartas_mao);

        Carta* carta_jogador = remover_carta_por_posicao(&jogador1.mao, escolha_jogador_pos);
        
        int num_cartas_cpu = contar_cartas(cpu.mao);
        if (num_cartas_cpu == 0) {
            printf("Erro: CPU ficou sem cartas!\n");
            break;
        }
        
        int escolha_cpu_pos = (rand() % num_cartas_cpu) + 1;
        Carta* carta_cpu = remover_carta_por_posicao(&cpu.mao, escolha_cpu_pos);

        if (carta_jogador == NULL || carta_cpu == NULL) {
            printf("Erro: Falha ao obter cartas!\n");
            break;
        }

        printf("\nVocê jogou: [%s]\n", tipo_para_string(carta_jogador->tipo));
        printf("CPU jogou:   [%s]\n", tipo_para_string(carta_cpu->tipo));

        ResultadoRodada resultado = comparar_cartas(carta_jogador->tipo, carta_cpu->tipo);
        switch (resultado) {
            case VITORIA:
                printf(">>> Você venceu a rodada! <<<\n");
                jogador1.pontos_rodada++;
                pausar_tela(2000);
                limpar_tela();
                break;
            case DERROTA:
                printf(">>> CPU venceu a rodada! <<<\n");
                cpu.pontos_rodada++;
                pausar_tela(2000);
                limpar_tela();
                break;
            case EMPATE:
                printf(">>> Empate! <<<\n");
                pausar_tela(2000);
                limpar_tela();
                break;
        }

        adicionar_carta_inicio(&descarte, carta_jogador->tipo);
        adicionar_carta_inicio(&descarte, carta_cpu->tipo);
        free(carta_jogador);
        free(carta_cpu);

        if (contar_cartas(jogador1.mao) < config.tamanho_mao) {
             comprar_carta(&baralho, &jogador1.mao);
             comprar_carta(&baralho, &cpu.mao);
        }

        if(baralho == NULL && descarte != NULL) {
            printf("\n--- O baralho acabou! Reembaralhando o descarte... ---\n");
            pausar_tela(2000);
            baralho = descarte;
            descarte = NULL;
            embaralhar(&baralho);
        }
        rodada_atual++;
    }

    printf("\n================ FIM DE JOGO ================\n");
    int vitorias, derrotas;
    ler_placar(&vitorias, &derrotas);

    if (jogador1.pontos_rodada > cpu.pontos_rodada) {
        printf("PARABÉNS! Você venceu a partida!\n");
        vitorias++;
    } else {
        printf("QUE PENA! A CPU venceu a partida.\n");
        derrotas++;
    }
    salvar_placar(vitorias, derrotas);
    printf("Placar geral atualizado: %d/%d\n", vitorias, derrotas);    printf("===========================================\n\n");
    printf("Pressione Enter para continuar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();

    liberar_lista(&jogador1.mao);
    liberar_lista(&cpu.mao);
    liberar_lista(&baralho);
    liberar_lista(&descarte);
}