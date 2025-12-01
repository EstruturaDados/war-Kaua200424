#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// =============================
// PROTÓTIPOS
// =============================
void atribuirMissao(char* destino, char* missoes[], int total);
int verificarMissao(char* missao, Territorio* mapa, int tamanho, const char* corJogador);

// =============================
// FUNÇÃO: SORTEAR MISSÃO
// =============================
void atribuirMissao(char* destino, char* missoes[], int total) {
    int i = rand() % total;
    strcpy(destino, missoes[i]);
}

// =============================
// FUNÇÃO: VERIFICAR MISSÃO
// =============================
int verificarMissao(char* missao, Territorio* mapa, int tamanho, const char* corJogador) {

    // MISSÃO 1: Conquistar 3 territórios seguidos
    if (strstr(missao, "3 territorios seguidos") != NULL) {
        int seguidos = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                seguidos++;
                if (seguidos >= 3) return 1;
            } else {
                seguidos = 0;
            }
        }
        return 0;
    }

    // MISSÃO 2: Eliminar tropas vermelhas
    if (strstr(missao, "vermelha") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0)
                return 0;
        }
        return 1;
    }

    // MISSÃO 3: Controlar todos os territórios
    if (strstr(missao, "todos os territorios") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) != 0)
                return 0;
        }
        return 1;
    }

    // MISSÃO 4: Ter 10 tropas em algum
    if (strstr(missao, "10 tropas") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas >= 10)
                return 1;
        }
        return 0;
    }

    // MISSÃO 5: Conquistar território central (índice 2)
    if (strstr(missao, "territorio central") != NULL) {
        if (strcmp(mapa[tamanho/2].cor, corJogador) == 0)
            return 1;
        return 0;
    }

    return 0;
}


// =============================
// PROGRAMA PRINCIPAL
// =============================
int main() {
    srand(time(NULL));

    const char* corJogador = "azul";

    // MISSOES
    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar todos os territorios do mapa",
        "Manter pelo menos 10 tropas em um territorio",
        "Conquistar o territorio central"
    };
    int totalMissoes = 5;

    // ALOCAÇÃO DINÂMICA DA MISSÃO
    char* missaoJogador = malloc(200);
    atribuirMissao(missaoJogador, missoes, totalMissoes);

    printf("\nMISSÃO SORTEADA PARA O JOGADOR:\n>> %s <<\n", missaoJogador);

    // MAPA DE EXEMPLO
    int tamanho = 5;
    Territorio mapa[5] = {
        {"A", "azul", 3},
        {"B", "vermelha", 2},
        {"C", "verde", 4},
        {"D", "vermelha", 1},
        {"E", "azul", 2}
    };

    // =============================
    // LOOP DE TURNOS
    // =============================
    for (int turno = 1; turno <= 10; turno++) {
        printf("\n=== TURNO %d ===\n", turno);

        // ---- SIMULAÇÕES PARA PERMITIR CUMPRIR MISSÕES ----
        
        // a cada turno, jogador conquista um novo território
        if (turno <= tamanho) {
            strcpy(mapa[turno - 1].cor, corJogador);
            mapa[turno - 1].tropas += turno;
        }

        // reduz tropas vermelhas
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0) {
                mapa[i].tropas -= 1;
                if (mapa[i].tropas < 0) mapa[i].tropas = 0;
            }
        }

        // ---- CHECAR MISSÃO ----
        if (verificarMissao(missaoJogador, mapa, tamanho, corJogador)) {
            printf("\n🏆 O JOGADOR VENCEU O JOGO! 🏆\n");
            printf("Missão cumprida: %s\n", missaoJogador);
            free(missaoJogador);
            return 0;
        }

        printf("Missão ainda não cumprida.\n");
    }

    printf("\nNENHUM VENCEDOR (isso só ocorre se você quiser).\n");

    free(missaoJogador);
    return 0;
}

