// Desafio Batalha Naval - MateCheck

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NUM_NAVIOS 4
#define TAMANHO_HABILIDADE 5
#define VALOR_AGUA 0
#define VALOR_NAVIO 3
#define VALOR_HABILIDADE 5

// Estrutura para representar uma habilidade
typedef struct {
    char nome[20];
    int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int centroX;
    int centroY;
} Habilidade;

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
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
    return (tabuleiro[linha][coluna] != VALOR_AGUA);
}

// Funções para posicionar navios (mantidas do nível anterior)
int posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                             int linha, int coluna, int tamanho) {
    if (coluna + tamanho > TAMANHO_TABULEIRO) return 0;
    for (int j = coluna; j < coluna + tamanho; j++) {
        if (verificarSobreposicao(tabuleiro, linha, j)) return 0;
    }
    for (int j = coluna; j < coluna + tamanho; j++) {
        tabuleiro[linha][j] = VALOR_NAVIO;
    }
    return 1;
}

int posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                           int linha, int coluna, int tamanho) {
    if (linha + tamanho > TAMANHO_TABULEIRO) return 0;
    for (int i = linha; i < linha + tamanho; i++) {
        if (verificarSobreposicao(tabuleiro, i, coluna)) return 0;
    }
    for (int i = linha; i < linha + tamanho; i++) {
        tabuleiro[i][coluna] = VALOR_NAVIO;
    }
    return 1;
}

// Função para criar matriz de habilidade em formato de Cone
void criarHabilidadeCone(Habilidade *hab) {
    sprintf(hab->nome, "Cone");
    int centro = TAMANHO_HABILIDADE / 2;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cone: forma triangular apontando para baixo
            if (i >= centro && abs(j - centro) <= (i - centro)) {
                hab->matriz[i][j] = 1;
            } else {
                hab->matriz[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade em formato de Cruz
void criarHabilidadeCruz(Habilidade *hab) {
    sprintf(hab->nome, "Cruz");
    int centro = TAMANHO_HABILIDADE / 2;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cruz: linha central + coluna central
            if (i == centro || j == centro) {
                hab->matriz[i][j] = 1;
            } else {
                hab->matriz[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade em formato de Octaedro (Losango)
void criarHabilidadeOctaedro(Habilidade *hab) {
    sprintf(hab->nome, "Octaedro");
    int centro = TAMANHO_HABILIDADE / 2;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Octaedro: formato de losango
            int dist = abs(i - centro) + abs(j - centro);
            if (dist <= centro) {
                hab->matriz[i][j] = 1;
            } else {
                hab->matriz[i][j] = 0;
            }
        }
    }
}

// Função para exibir uma matriz de habilidade
void exibirMatrizHabilidade(Habilidade hab) {
    printf("\nMatriz de %s (%dx%d):\n", hab.nome, TAMANHO_HABILIDADE, TAMANHO_HABILIDADE);
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            printf("%d ", hab.matriz[i][j]);
        }
        printf("\n");
    }
}

// Função para aplicar uma habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                      Habilidade hab, int centroTabuleiroX, int centroTabuleiroY) {
    int offset = TAMANHO_HABILIDADE / 2;
    
    printf("Aplicando %s no centro (%d, %d)\n", hab.nome, centroTabuleiroX, centroTabuleiroY);
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (hab.matriz[i][j] == 1) {
                int tabuleiroX = centroTabuleiroX - offset + i;
                int tabuleiroY = centroTabuleiroY - offset + j;
                
                if (posicaoValida(tabuleiroX, tabuleiroY)) {
                    // Marcar área afetada pela habilidade
                    tabuleiro[tabuleiroX][tabuleiroY] = VALOR_HABILIDADE;
                }
            }
        }
    }
}

// Função para exibir o tabuleiro de forma organizada
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO COM HABILIDADES ===\n\n");
    
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

// Função para exibir o tabuleiro com símbolos visuais
void exibirTabuleiroVisual(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== VISUALIZAÇÃO DO TABULEIRO ===\n\n");
    printf("    ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n    ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("---");
    }
    printf("\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d |", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            switch (tabuleiro[i][j]) {
                case VALOR_AGUA:
                    printf(" . ");      // Água
                    break;
                case VALOR_NAVIO:
                    printf(" █ ");      // Navio
                    break;
                case VALOR_HABILIDADE:
                    printf(" X ");      // Área de habilidade
                    break;
                default:
                    printf(" ? ");      // Desconhecido
            }
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializar o tabuleiro
    inicializarTabuleiro(tabuleiro);
    
    printf("=== SISTEMA DE HABILIDADES ESPECIAIS ===\n");
    
    // Posicionar alguns navios para demonstração
    posicionarNavioHorizontal(tabuleiro, 2, 2, TAMANHO_NAVIO);
    posicionarNavioVertical(tabuleiro, 5, 7, TAMANHO_NAVIO);
    posicionarNavioHorizontal(tabuleiro, 8, 4, TAMANHO_NAVIO);
    
    // Criar habilidades
    Habilidade cone, cruz, octaedro;
    
    criarHabilidadeCone(&cone);
    criarHabilidadeCruz(&cruz);
    criarHabilidadeOctaedro(&octaedro);
    
    // Exibir matrizes de habilidades
    exibirMatrizHabilidade(cone);
    exibirMatrizHabilidade(cruz);
    exibirMatrizHabilidade(octaedro);
    
    // Definir centros das habilidades no tabuleiro
    int centroConeX = 3, centroConeY = 3;
    int centroCruzX = 6, centroCruzY = 6;
    int centroOctaedroX = 8, centroOctaedroY = 8;
    
    // Aplicar habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, centroConeX, centroConeY);
    aplicarHabilidade(tabuleiro, cruz, centroCruzX, centroCruzY);
    aplicarHabilidade(tabuleiro, octaedro, centroOctaedroX, centroOctaedroY);
    
    // Exibir resultados
    printf("\n=== RESULTADOS FINAIS ===\n");
    
    // Exibir tabuleiro numérico
    exibirTabuleiro(tabuleiro);
    
    // Exibir tabuleiro visual com símbolos
    exibirTabuleiroVisual(tabuleiro);
    
    printf("\n=== LEGENDA ===\n");
    printf(". - Água\n");
    printf("█ - Navio\n");
    printf("X - Área afetada por habilidade\n");
    printf("\nCentros das habilidades:\n");
    printf("Cone: (%d, %d)\n", centroConeX, centroConeY);
    printf("Cruz: (%d, %d)\n", centroCruzX, centroCruzY);
    printf("Octaedro: (%d, %d)\n", centroOctaedroX, centroOctaedroY);
    
    return 0;
}
