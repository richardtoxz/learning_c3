#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>

void limpar_tela() {
    system("cls");
}

void pausar_tela(int milissegundos) {
    Sleep(milissegundos);
}

#else
#include <unistd.h>

void limpar_tela() {
    system("clear");
}

void pausar_tela(int milissegundos) {
    usleep(milissegundos * 1000);
}

#endif

int ler_inteiro_seguro(const char* prompt, int min, int max) {
    int valor;
    char buffer[50];
    
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &valor) == 1) {
                if (valor >= min && valor <= max) {
                    return valor;
                } else {
                    printf("Valor deve estar entre %d e %d. Tente novamente.\n", min, max);
                }
            } else {
                printf("Entrada inválida. Digite um número.\n");
            }
        }
    }
}