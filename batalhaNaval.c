#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3
#define VALOR_HABILIDADE 5
#define TAMANHO_HABILIDADE 5  // Matrizes 5x5 para habilidades

// Exibe o tabuleiro com símbolos diferentes para facilitar a visualização
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO ===\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == VALOR_AGUA) printf("~ ");
            else if (tabuleiro[i][j] == VALOR_NAVIO) printf("N ");
            else if (tabuleiro[i][j] == VALOR_HABILIDADE) printf("* ");
            else printf("? "); // fallback
        }
        printf("\n");
    }
}

// Verifica se há navio na posição
int estaOcupado(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    return tabuleiro[linha][coluna] == VALOR_NAVIO;
}

// Posiciona navio horizontal
int posicionarHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        if (estaOcupado(tabuleiro, linha, coluna + i)) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[linha][coluna + i] = VALOR_NAVIO;
    return 1;
}

// Posiciona navio vertical
int posicionarVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        if (estaOcupado(tabuleiro, linha + i, coluna)) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[linha + i][coluna] = VALOR_NAVIO;
    return 1;
}

// Diagonal ↘
int posicionarDiagonalPrincipal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        if (estaOcupado(tabuleiro, linha + i, coluna + i)) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[linha + i][coluna + i] = VALOR_NAVIO;
    return 1;
}

// Diagonal ↙
int posicionarDiagonalSecundaria(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna - TAMANHO_NAVIO + 1 < 0) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        if (estaOcupado(tabuleiro, linha + i, coluna - i)) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[linha + i][coluna - i] = VALOR_NAVIO;
    return 1;
}

// Aplica matriz de habilidade (5x5) no tabuleiro, centralizando em (linha, coluna)
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[5][5], int linha_centro, int coluna_centro) {
    int offset = TAMANHO_HABILIDADE / 2; // deslocamento do centro

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linha_real = linha_centro - offset + i;
            int coluna_real = coluna_centro - offset + j;

            // Garante que a posição está dentro do tabuleiro
            if (linha_real >= 0 && linha_real < TAMANHO_TABULEIRO &&
                coluna_real >= 0 && coluna_real < TAMANHO_TABULEIRO &&
                habilidade[i][j] == 1 &&
                tabuleiro[linha_real][coluna_real] == VALOR_AGUA) {

                tabuleiro[linha_real][coluna_real] = VALOR_HABILIDADE;
            }
        }
    }
}

// Gera uma matriz em forma de cone (base para baixo)
void gerarCone(int matriz[5][5]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i >= abs(2 - j)) // lógica do cone
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera uma matriz em forma de cruz
void gerarCruz(int matriz[5][5]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == 2 || j == 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera uma matriz em forma de octaedro (losango)
void gerarOctaedro(int matriz[5][5]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com água
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
            tabuleiro[i][j] = VALOR_AGUA;

    // Posiciona navios
    posicionarHorizontal(tabuleiro, 2, 4);
    posicionarVertical(tabuleiro, 5, 1);
    posicionarDiagonalPrincipal(tabuleiro, 0, 0);
    posicionarDiagonalSecundaria(tabuleiro, 0, 9);

    // Matrizes de habilidades
    int cone[5][5], cruz[5][5], octaedro[5][5];

    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    // Aplica as habilidades em posições escolhidas (definidas no código)
    aplicarHabilidade(tabuleiro, cone, 6, 6);       // centro do cone
    aplicarHabilidade(tabuleiro, cruz, 4, 4);       // centro da cruz
    aplicarHabilidade(tabuleiro, octaedro, 7, 2);   // centro do octaedro

    // Exibe o tabuleiro final com navios e habilidades
    exibirTabuleiro(tabuleiro);

    return 0;
}
