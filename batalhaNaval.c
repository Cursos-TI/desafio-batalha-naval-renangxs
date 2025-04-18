#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3

// Função para imprimir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO ===\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // 1. Inicializar o tabuleiro com 0 (água)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
        }
    }

    // 2. Coordenadas iniciais dos navios (definidas no código)
    int linha_horizontal = 2, coluna_horizontal = 4; // Navio horizontal começando na (2,4)
    int linha_vertical = 5, coluna_vertical = 1;     // Navio vertical começando na (5,1)

    // 3. Verificação de validade de posições
    if (coluna_horizontal + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
        linha_vertical + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: Navio ultrapassa os limites do tabuleiro.\n");
        return 1;
    }

    // 4. Verificar sobreposição antes de posicionar os navios
    int sobreposicao = 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha_horizontal][coluna_horizontal + i] == VALOR_NAVIO ||
            tabuleiro[linha_vertical + i][coluna_vertical] == VALOR_NAVIO) {
            sobreposicao = 1;
            break;
        }
    }

    if (sobreposicao) {
        printf("Erro: Navios sobrepostos!\n");
        return 1;
    }

    // 5. Posicionar o navio horizontal
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha_horizontal][coluna_horizontal + i] = VALOR_NAVIO;
    }

    // 6. Posicionar o navio vertical
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha_vertical + i][coluna_vertical] = VALOR_NAVIO;
    }

    // 7. Exibir o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}
