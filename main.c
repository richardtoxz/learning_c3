#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "configuracoes.h"
#include "jogo.h"
#include "placar.h"
#include "utils.h"

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand(time(NULL));

    Configuracoes config = {
        .pontos_para_vencer = 2,
        .tamanho_baralho = 30,
        .compra_limitada = false,
        .tamanho_mao = 5
    };

    int opcao;
    do {
        limpar_tela();
        printf("========================================\n");
        printf("| JOGO DE CARTAS: PEDRA, PAPEL, TESOURA |\n");
        printf("========================================\n");
        printf("MENU PRINCIPAL\n");
        printf("1. Iniciar Partida\n");
        printf("2. Pontuação\n");
        printf("3. Configurações\n");
        printf("4. Sair\n");        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcao) {
            case 1:
                iniciar_partida(config);
                break;
            case 2:
                exibir_winrate();
                break;
            case 3:
                menu_configuracoes(&config);
                break;
            case 4:
                printf("Obrigado por jogar!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 4);

    return 0;
}