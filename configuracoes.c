#include <stdio.h>
#include <locale.h>
#include "configuracoes.h"
#include "utils.h"

void menu_configuracoes(Configuracoes *config) {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int opcao;
    int md_opcao;
    int novo_tamanho_baralho;

    do {
        limpar_tela();
        printf("\n--- CONFIGURAÇÕES ---\n");
        printf("1. Definir Modo de Jogo (Atual: MD%d)\n", (config->pontos_para_vencer * 2) - 1);
        printf("2. Tamanho do Baralho (Atual: %d cartas)\n", config->tamanho_baralho);
        printf("3. Limite de Compra por Round (Atual: %s)\n", config->compra_limitada ? "Ativado" : "Desativado");
        printf("4. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcao) {
            case 1:
                printf("Escolha o modo (1, 3, 5, 7 para MD1, MD3, etc.): ");
                scanf("%d", &md_opcao);
                if (md_opcao == 1 || md_opcao == 3 || md_opcao == 5 || md_opcao == 7) {
                    config->pontos_para_vencer = (md_opcao / 2) + 1;
                    printf("Modo de jogo alterado para Melhor de %d.\n", md_opcao);
                } else {
                    printf("Opção inválida!\n");
                }
                break;
            case 2:
                printf("Digite o novo tamanho do baralho (múltiplo de 3, max 30): ");
                scanf("%d", &novo_tamanho_baralho);
                if (novo_tamanho_baralho > 0 && novo_tamanho_baralho <= 30 && novo_tamanho_baralho % 3 == 0) {
                    config->tamanho_baralho = novo_tamanho_baralho;
                    printf("Tamanho do baralho alterado para %d.\n", novo_tamanho_baralho);
                } else {
                    printf("Valor inválido! Deve ser um múltiplo de 3 e no máximo 30.\n");
                }
                break;
            case 3:
                config->compra_limitada = !config->compra_limitada;
                printf("Limite de compra por round %s.\n", config->compra_limitada ? "ativado" : "desativado");
                break;
            case 4:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 4);
}