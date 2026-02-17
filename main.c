#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

#define MAX_EQ 100
#define MAX_MED 500
#define NUM_GRANDEZAS 4

/* ================= ESTRUTURAS ================= */

typedef struct {
    int id;
    char nome[60];
    char tipo[30];
} Equipamento;

typedef struct {
    int idEq;
    char grandeza; 
    float valor;
} Medicao;

/* ================= DADOS GLOBAIS ================= */

Equipamento equipamentos[MAX_EQ];
Medicao medicoes[MAX_MED];
int qtdEq = 0;
int qtdMed = 0;

/* ================= UTILITÁRIOS ================= */

void limparBuffer() {
    while (getchar() != '\n');
}

int buscarEquipamento(int id) {
    for (int i = 0; i < qtdEq; i++)
        if (equipamentos[i].id == id)
            return i;
    return -1;
}

int indiceGrandeza(char g) {
    switch (g) {
        case 'V': return 0;
        case 'I': return 1;
        case 'P': return 2;
        case 'T': return 3;
        default: return -1;
    }
}

/* ================= FUNCIONALIDADES ================= */

void cadastrarEquipamento() {
    if (qtdEq >= MAX_EQ) {
        printf("\n[ERRO] Limite de equipamentos atingido.\n");
        return;
    }

    int id;
    printf("\nID do Equipamento: ");
    if (scanf("%d", &id) != 1) {
        printf("[ERRO] Entrada invalida.\n");
        limparBuffer();
        return;
    }

    if (buscarEquipamento(id) != -1) {
        printf("[ERRO] ID %d ja existe no sistema.\n", id);
        return;
    }

    equipamentos[qtdEq].id = id;

    printf("Nome: ");
    scanf(" %[^\n]", equipamentos[qtdEq].nome);

    printf("Tipo: ");
    scanf(" %[^\n]", equipamentos[qtdEq].tipo);

    qtdEq++;
    printf("Sucesso: Equipamento cadastrado.\n");
}

void registrarMedicao() {
    if (qtdMed >= MAX_MED) {
        printf("\n[ERRO] Limite de medicoes atingido.\n");
        return;
    }

    int id;
    printf("\nID do equipamento: ");
    if (scanf("%d", &id) != 1) {
        printf("[ERRO] ID invalido.\n");
        limparBuffer();
        return;
    }

    if (buscarEquipamento(id) == -1) {
        printf("[ERRO] Equipamento nao encontrado.\n");
        return;
    }

    char g;
    printf("Grandeza (V/I/P/T): ");
    if (scanf(" %c", &g) != 1) {
        printf("[ERRO] Entrada invalida.\n");
        limparBuffer();
        return;
    }

    g = toupper(g);       // Converte antes da validação
    limparBuffer();       // Limpa buffer após leitura do char

    if (indiceGrandeza(g) == -1) {
        printf("[ERRO] Grandeza invalida.\n");
        return;
    }

    float valor;
    printf("Valor medido: ");
    if (scanf("%f", &valor) != 1) {
        printf("[ERRO] Valor invalido.\n");
        limparBuffer();
        return;
    }

    medicoes[qtdMed].idEq = id;
    medicoes[qtdMed].grandeza = g;
    medicoes[qtdMed].valor = valor;
    qtdMed++;

    printf("Sucesso: Medicao registrada.\n");
}

void listarDados() {
    if (qtdEq == 0) {
        printf("\nNenhum dado cadastrado.\n");
        return;
    }

    printf("\n--- LISTAGEM DE EQUIPAMENTOS ---\n");
    printf("%-6s | %-25s | %-15s\n", "ID", "NOME", "TIPO");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < qtdEq; i++) {
        printf("%-6d | %-25s | %-15s\n",
               equipamentos[i].id,
               equipamentos[i].nome,
               equipamentos[i].tipo);
    }

    if (qtdMed > 0) {
        printf("\n--- LISTAGEM DE MEDICOES ---\n");
        printf("%-8s | %-10s | %-10s\n", "ID EQ", "GRANDEZA", "VALOR");
        printf("--------------------------------------------\n");

        for (int i = 0; i < qtdMed; i++) {
            printf("%-8d | %-10c | %-10.2f\n",
                   medicoes[i].idEq,
                   medicoes[i].grandeza,
                   medicoes[i].valor);
        }
    }
}

/* ================= RELATÓRIO ================= */

void gerarRelatorios() {
    if (qtdMed == 0) {
        printf("\nNao ha dados para gerar relatorios.\n");
        return;
    }

    float matrizSoma[MAX_EQ][NUM_GRANDEZAS] = {0};
    int matrizCont[MAX_EQ][NUM_GRANDEZAS] = {0};
    
    float minG[NUM_GRANDEZAS], maxG[NUM_GRANDEZAS];

    for (int i = 0; i < NUM_GRANDEZAS; i++) {
        minG[i] = FLT_MAX;
        maxG[i] = -FLT_MAX;
    }

    for (int i = 0; i < qtdMed; i++) {
        int idxEq = buscarEquipamento(medicoes[i].idEq);
        int idxG = indiceGrandeza(medicoes[i].grandeza);

        if (idxEq != -1 && idxG != -1) {
            matrizSoma[idxEq][idxG] += medicoes[i].valor;
            matrizCont[idxEq][idxG]++;

            if (medicoes[i].valor < minG[idxG]) minG[idxG] = medicoes[i].valor;
            if (medicoes[i].valor > maxG[idxG]) maxG[idxG] = medicoes[i].valor;
        }
    }

    char letras[] = {'V', 'I', 'P', 'T'};

    printf("\n================ RELATORIO DE MEDIAS ================\n");

    for (int i = 0; i < qtdEq; i++) {
        printf("Equipamento: %-20s | ID: %-5d\n",
               equipamentos[i].nome,
               equipamentos[i].id);

        printf("%-10s | %-10s\n", "GRANDEZA", "MEDIA");
        printf("----------------------------\n");

        int temMedicao = 0;

        for (int j = 0; j < NUM_GRANDEZAS; j++) {
            if (matrizCont[i][j] > 0) {
                printf("%-10c | %-10.2f\n",
                       letras[j],
                       matrizSoma[i][j] / matrizCont[i][j]);
                temMedicao = 1;
            }
        }

        if (!temMedicao) {
            printf("Sem medicoes registradas.\n");
        }

        printf("--------------------------------------\n");
    }

    printf("\n========= VALORES EXTREMOS POR GRANDEZA =========\n");
    printf("%-10s | %-10s | %-10s\n", "GRANDEZA", "MINIMO", "MAXIMO");
    printf("--------------------------------------------\n");

    for (int j = 0; j < NUM_GRANDEZAS; j++) {
        if (minG[j] != FLT_MAX) {
            printf("%-10c | %-10.2f | %-10.2f\n",
                   letras[j],
                   minG[j],
                   maxG[j]);
        }
    }
}

/* ================= MAIN ================= */

int main() {
    int opcao;

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Cadastrar Equipamento\n");
        printf("2. Registrar Medicao\n");
        printf("3. Listar Equipamentos e Medicoes\n");
        printf("4. Relatorios (Medias, Min, Max)\n");
        printf("5. Sair\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Use apenas numeros.\n");
            limparBuffer();
            opcao = 0;
            continue;
        }

        switch (opcao) {
            case 1: cadastrarEquipamento(); break;
            case 2: registrarMedicao(); break;
            case 3: listarDados(); break;
            case 4: gerarRelatorios(); break;
            case 5: printf("\nEncerrando programa...\n"); break;
            default: printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 5);

    return 0;
}
