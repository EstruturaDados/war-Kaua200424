#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

Territorio* cadastrarTerritorios(int qtd);
void exibirTerritorios(Territorio* vet, int qtd);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* vet);

int main() {
    srand(time(NULL));

    int qtd;
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);

    Territorio* territorios = cadastrarTerritorios(qtd);

    int atacarID, defenderID;

    while (1) {
        printf("\n=== TERRITORIOS DISPONIVEIS ===\n");
        exibirTerritorios(territorios, qtd);

        printf("\nDigite o ID do territorio atacante (-1 para sair): ");
        scanf("%d", &atacarID);

        if (atacarID == -1) break; 

        printf("Digite o ID do territorio defensor: ");
        scanf("%d", &defenderID);

        if (atacarID < 0 || atacarID >= qtd || defenderID < 0 || defenderID >= qtd) {
            printf("IDs invalidos!\n");
            continue;
        }

        if (atacarID == defenderID) {
            printf("Um territorio nao pode atacar ele mesmo!\n");
            continue;
        }

        atacar(&territorios[atacarID], &territorios[defenderID]);

        printf("\n=== ESTADO APOS O ATAQUE ===\n");
        exibirTerritorios(territorios, qtd);
    }

    liberarMemoria(territorios);
    return 0;
}

Territorio* cadastrarTerritorios(int qtd) {
    Territorio* vet = (Territorio*) calloc(qtd, sizeof(Territorio));

    if (vet == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do Territorio %d ---\n", i);

        printf("Nome: ");
        scanf(" %29s", vet[i].nome);

        printf("Cor do exercito: ");
        scanf(" %9s", vet[i].cor);

        printf("Numero de tropas: ");
        scanf("%d", &vet[i].tropas);
    }

    return vet;
}

void exibirTerritorios(Territorio* vet, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\nID: %d\n", i);
        printf("Nome: %s\n", vet[i].nome);
        printf("Cor: %s\n", vet[i].cor);
        printf("Tropas: %d\n", vet[i].tropas);
    }
}

void atacar(Territorio* atacante, Territorio* defensor) {

    printf("\n=== ATAQUE INICIADO ===\n");
    printf("%s (%s) ATACA %s (%s)\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    int dadoAtk = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("Dado atacante: %d\n", dadoAtk);
    printf("Dado defensor: %d\n", dadoDef);

    if (dadoAtk > dadoDef) {
        printf("Atacante venceu!\n");
        defensor->tropas -= 1;

        if (defensor->tropas <= 0) {
            printf("O territorio %s foi conquistado!\n", defensor->nome);
            strcpy(defensor->cor, atacante->cor);  
            defensor->tropas = atacante->tropas / 2; 
        }

    } else {
        printf("Defensor resistiu!\n");
        atacante->tropas -= 1;

        if (atacante->tropas < 0)
            atacante->tropas = 0;
    }
}

void liberarMemoria(Territorio* vet) {
    free(vet);
    printf("\nMemoria liberada com sucesso!\n");
}
