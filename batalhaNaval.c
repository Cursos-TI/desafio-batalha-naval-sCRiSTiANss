// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }
}

int posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                             int linha, int coluna, int tamanho) {
    // Verificar se o navio cabe horizontalmente
    if (coluna + tamanho > TAMANHO_TABULEIRO) {
        return 0; // Posição inválida
    }
    
    // Verificar se não há sobreposição
    for (int j = coluna; j < coluna + tamanho; j++) {
        if (tabuleiro[linha][j] != 0) {
            return 0; // Já tem navio nesta posição
        }
    }
    
    // Posicionar o navio
    for (int j = coluna; j < coluna + tamanho; j++) {
        tabuleiro[linha][j] = 3; // 3 representa parte do navio
    }
    
    return 1; // Posicionamento bem-sucedido
}

int posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                           int linha, int coluna, int tamanho) {
    // Verificar se o navio cabe verticalmente
    if (linha + tamanho > TAMANHO_TABULEIRO) {
        return 0; // Posição inválida
    }
    
    // Verificar se não há sobreposição
    for (int i = linha; i < linha + tamanho; i++) {
        if (tabuleiro[i][coluna] != 0) {
            return 0; // Já tem navio nesta posição
        }
    }
    
    // Posicionar o navio
    for (int i = linha; i < linha + tamanho; i++) {
        tabuleiro[i][coluna] = 3; // 3 representa parte do navio
    }
    
    return 1; // Posicionamento bem-sucedido
}

void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    
    // Imprimir números das colunas
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    // Imprimir linha separadora
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("---");
    }
    printf("\n");
    
    // Imprimir tabuleiro com números das linhas
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d|", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializar o tabuleiro com água (0)
    inicializarTabuleiro(tabuleiro);
    
    printf("=== POSICIONAMENTO DE NAVIOS ===\n");
    
    // Posicionar navio horizontal (coordenadas definidas no código)
    int linha_horizontal = 2;
    int coluna_horizontal = 3;
    
    if (posicionarNavioHorizontal(tabuleiro, linha_horizontal, coluna_horizontal, TAMANHO_NAVIO)) {
        printf("Navio horizontal posicionado com sucesso na linha %d, coluna %d\n", 
               linha_horizontal, coluna_horizontal);
    } else {
        printf("Erro: Não foi possível posicionar o navio horizontal nas coordenadas (%d, %d)\n", 
               linha_horizontal, coluna_horizontal);
        return 1;
    }
    
    // Posicionar navio vertical (coordenadas definidas no código)
    int linha_vertical = 5;
    int coluna_vertical = 7;
    
    if (posicionarNavioVertical(tabuleiro, linha_vertical, coluna_vertical, TAMANHO_NAVIO)) {
        printf("Navio vertical posicionado com sucesso na linha %d, coluna %d\n", 
               linha_vertical, coluna_vertical);
    } else {
        printf("Erro: Não foi possível posicionar o navio vertical nas coordenadas (%d, %d)\n", 
               linha_vertical, coluna_vertical);
        return 1;
    }
    
    // Exibir o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);
    
    printf("\nLegenda:\n");
    printf("0 - Água\n");
    printf("3 - Parte de navio\n");
    
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

