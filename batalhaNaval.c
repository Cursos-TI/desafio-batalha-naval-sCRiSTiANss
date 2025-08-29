// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NUM_NAVIOS 4

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }
}

// Função para verificar se uma posição está dentro dos limites do tabuleiro
int posicaoValida(int linha, int coluna) {
    return (linha >= 0 && linha < TAMANHO_TABULEIRO && 
            coluna >= 0 && coluna < TAMANHO_TABULEIRO);
}

// Função para verificar se há sobreposição em uma posição específica
int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                         int linha, int coluna) {
    return (tabuleiro[linha][coluna] != 0);
}

// Função para posicionar navio horizontal
int posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                             int linha, int coluna, int tamanho) {
    // Verificar se o navio cabe horizontalmente
    if (coluna + tamanho > TAMANHO_TABULEIRO) {
        printf("Erro: Navio horizontal não cabe a partir da coluna %d\n", coluna);
        return 0;
    }
    
    // Verificar se não há sobreposição
    for (int j = coluna; j < coluna + tamanho; j++) {
        if (verificarSobreposicao(tabuleiro, linha, j)) {
            printf("Erro: Sobreposição no navio horizontal em (%d, %d)\n", linha, j);
            return 0;
        }
    }
    
    // Posicionar o navio
    for (int j = coluna; j < coluna + tamanho; j++) {
        tabuleiro[linha][j] = 3; // 3 representa parte do navio
    }
    
    return 1;
}

// Função para posicionar navio vertical
int posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                           int linha, int coluna, int tamanho) {
    // Verificar se o navio cabe verticalmente
    if (linha + tamanho > TAMANHO_TABULEIRO) {
        printf("Erro: Navio vertical não cabe a partir da linha %d\n", linha);
        return 0;
    }
    
    // Verificar se não há sobreposição
    for (int i = linha; i < linha + tamanho; i++) {
        if (verificarSobreposicao(tabuleiro, i, coluna)) {
            printf("Erro: Sobreposição no navio vertical em (%d, %d)\n", i, coluna);
            return 0;
        }
    }
    
    // Posicionar o navio
    for (int i = linha; i < linha + tamanho; i++) {
        tabuleiro[i][coluna] = 3; // 3 representa parte do navio
    }
    
    return 1;
}

// Função para posicionar navio diagonal (canto superior esquerdo para inferior direito)
int posicionarNavioDiagonal1(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                            int linha, int coluna, int tamanho) {
    // Verificar se o navio cabe na diagonal
    if (linha + tamanho > TAMANHO_TABULEIRO || coluna + tamanho > TAMANHO_TABULEIRO) {
        printf("Erro: Navio diagonal não cabe a partir de (%d, %d)\n", linha, coluna);
        return 0;
    }
    
    // Verificar se não há sobreposição
    for (int i = 0; i < tamanho; i++) {
        int novaLinha = linha + i;
        int novaColuna = coluna + i;
        if (verificarSobreposicao(tabuleiro, novaLinha, novaColuna)) {
            printf("Erro: Sobreposição no navio diagonal em (%d, %d)\n", novaLinha, novaColuna);
            return 0;
        }
    }
    
    // Posicionar o navio
    for (int i = 0; i < tamanho; i++) {
        int novaLinha = linha + i;
        int novaColuna = coluna + i;
        tabuleiro[novaLinha][novaColuna] = 3; // 3 representa parte do navio
    }
    
    return 1;
}

// Função para posicionar navio diagonal (canto superior direito para inferior esquerdo)
int posicionarNavioDiagonal2(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                            int linha, int coluna, int tamanho) {
    // Verificar se o navio cabe na diagonal
    if (linha + tamanho > TAMANHO_TABULEIRO || coluna - tamanho + 1 < 0) {
        printf("Erro: Navio diagonal não cabe a partir de (%d, %d)\n", linha, coluna);
        return 0;
    }
    
    // Verificar se não há sobreposição
    for (int i = 0; i < tamanho; i++) {
        int novaLinha = linha + i;
        int novaColuna = coluna - i;
        if (verificarSobreposicao(tabuleiro, novaLinha, novaColuna)) {
            printf("Erro: Sobreposição no navio diagonal em (%d, %d)\n", novaLinha, novaColuna);
            return 0;
        }
    }
    
    // Posicionar o navio
    for (int i = 0; i < tamanho; i++) {
        int novaLinha = linha + i;
        int novaColuna = coluna - i;
        tabuleiro[novaLinha][novaColuna] = 3; // 3 representa parte do navio
    }
    
    return 1;
}

// Função para exibir o tabuleiro de forma organizada
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    
    // Imprimir números das colunas
    printf("    ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    // Imprimir linha separadora
    printf("    ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("---");
    }
    printf("\n");
    
    // Imprimir tabuleiro com números das linhas
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d |", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int naviosPosicionados = 0;
    
    // Inicializar o tabuleiro com água (0)
    inicializarTabuleiro(tabuleiro);
    
    printf("=== POSICIONAMENTO DE %d NAVIOS ===\n", NUM_NAVIOS);
    printf("Tamanho de cada navio: %d posições\n\n", TAMANHO_NAVIO);
    
    // Definir coordenadas dos navios (podem ser modificadas)
    int coordenadas[NUM_NAVIOS][3] = {
        {2, 1, 0},  // Horizontal: linha 2, coluna 1
        {5, 7, 1},  // Vertical: linha 5, coluna 7
        {1, 2, 2},  // Diagonal 1: linha 1, coluna 2
        {0, 8, 3}   // Diagonal 2: linha 0, coluna 8
    };
    
    // Posicionar navios
    for (int i = 0; i < NUM_NAVIOS; i++) {
        int sucesso = 0;
        int linha = coordenadas[i][0];
        int coluna = coordenadas[i][1];
        int tipo = coordenadas[i][2];
        
        switch (tipo) {
            case 0: // Horizontal
                sucesso = posicionarNavioHorizontal(tabuleiro, linha, coluna, TAMANHO_NAVIO);
                if (sucesso) printf("Navio horizontal posicionado em (%d, %d)\n", linha, coluna);
                break;
                
            case 1: // Vertical
                sucesso = posicionarNavioVertical(tabuleiro, linha, coluna, TAMANHO_NAVIO);
                if (sucesso) printf("Navio vertical posicionado em (%d, %d)\n", linha, coluna);
                break;
                
            case 2: // Diagonal 1 (↘)
                sucesso = posicionarNavioDiagonal1(tabuleiro, linha, coluna, TAMANHO_NAVIO);
                if (sucesso) printf("Navio diagonal (↘) posicionado em (%d, %d)\n", linha, coluna);
                break;
                
            case 3: // Diagonal 2 (↙)
                sucesso = posicionarNavioDiagonal2(tabuleiro, linha, coluna, TAMANHO_NAVIO);
                if (sucesso) printf("Navio diagonal (↙) posicionado em (%d, %d)\n", linha, coluna);
                break;
        }
        
        if (sucesso) {
            naviosPosicionados++;
        } else {
            printf("Falha ao posicionar navio %d\n", i + 1);
        }
        printf("\n");
    }
    
    // Exibir resultado final
    printf("=== RESULTADO FINAL ===\n");
    printf("Navios posicionados com sucesso: %d/%d\n\n", naviosPosicionados, NUM_NAVIOS);
    
    // Exibir o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);
    
    printf("\nLegenda:\n");
    printf("0 - Água\n");
    printf("3 - Parte de navio\n");
    printf("Direções: → Horizontal, ↓ Vertical, ↘ Diagonal1, ↙ Diagonal2\n");
    
    return 0;
}

    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

