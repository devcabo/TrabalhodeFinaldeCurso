#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

#define MAX_EQ 100
#define MAX_MED 500
#define NUM_GRANDEZAS 4

/* ================= TIPOS ================= */

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

/* ================= DADOS ================= */

Equipamento equipamentos[MAX_EQ];
Medicao medicoes[MAX_MED];

int qtdEq = 0;
int qtdMed = 0;

/* ================= UTIL ================= */

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

/* ================= ORDENAÇÃO ================= */

void ordenarEquipamentos() {
    for (int i = 0; i < qtdEq - 1; i++) {
        for (int j = i + 1; j < qtdEq; j++) {
            if (equipamentos[i].id > equipamentos[j].id) {
                Equipamento temp = equipamentos[i];
                equipamentos[i] = equipamentos[j];
                equipamentos[j] = temp;
            }
        }
    }
}

void ordenarMedicoes() {
    for (int i = 0; i < qtdMed - 1; i++) {
        for (int j = i + 1; j < qtdMed; j++) {
            if (medicoes[i].idEq > medicoes[j].idEq) {
                Medicao temp = medicoes[i];
                medicoes[i] = medicoes[j];
                medicoes[j] = temp;
            }
        }
    }
}

/* ================= CADASTRO ================= */

void cadastrarEquipamento() {

    if (qtdEq >= MAX_EQ) {
        printf("\nLimite atingido.\n");
        return;
    }

    int id;
    printf("\nID: ");
    if (scanf("%d", &id) != 1) {
        printf("Entrada invalida.\n");
        limparBuffer();
        return;
    }

    if (buscarEquipamento(id) != -1) {
        printf("ID ja existente.\n");
        return;
    }

    equipamentos[qtdEq].id = id;

    printf("Nome: ");
    scanf(" %[^\n]", equipamentos[qtdEq].nome);

    printf("Tipo: ");
    scanf(" %[^\n]", equipamentos[qtdEq].tipo);

    qtdEq++;
    ordenarEquipamentos();

    printf("Cadastrado com sucesso.\n");
}

/* ================= MEDIÇÃO ================= */

void registrarMedicao() {

    if (qtdMed >= MAX_MED) {
        printf("\nLimite atingido.\n");
        return;
    }

    int id;
    printf("\nID do equipamento: ");
    if (scanf("%d", &id) != 1) {
        printf("Entrada invalida.\n");
        limparBuffer();
        return;
    }

    if (buscarEquipamento(id) == -1) {
        printf("Equipamento nao encontrado.\n");
        return;
    }

    char g;
    printf("Grandeza (V/I/P/T): ");
    scanf(" %c", &g);
    g = toupper(g);
    limparBuffer();

    if (indiceGrandeza(g) == -1) {
        printf("Grandeza invalida.\n");
        return;
    }

    float valor;
    printf("Valor: ");
    if (scanf("%f", &valor) != 1) {
        printf("Entrada invalida.\n");
        limparBuffer();
        return;
    }

    medicoes[qtdMed].idEq = id;
    medicoes[qtdMed].grandeza = g;
    medicoes[qtdMed].valor = valor;

    qtdMed++;
    ordenarMedicoes();

    printf("Medicao registrada.\n");
}

/* ================= LISTAGENS ================= */

void listarEquipamentos() {

    if (qtdEq == 0) {
        printf("\nNenhum equipamento.\n");
        return;
    }

    printf("\n===== EQUIPAMENTOS =====\n");
    printf("%-10s %-20s %-20s\n", "ID", "Nome", "Tipo");

    for (int i = 0; i < qtdEq; i++)
        printf("%-10d %-20s %-20s\n",
               equipamentos[i].id,
               equipamentos[i].nome,
               equipamentos[i].tipo);
}

void listarMedicoes() {

    if (qtdMed == 0) {
        printf("\nNenhuma medicao.\n");
        return;
    }

    printf("\n===== MEDICOES =====\n");
    printf("%-10s %-10s %-10s\n", "ID", "G", "Valor");

    for (int i = 0; i < qtdMed; i++)
        printf("%-10d %-10c %-10.2f\n",
               medicoes[i].idEq,
               medicoes[i].grandeza,
               medicoes[i].valor);
}

/* ================= RELATÓRIOS ================= */

void calcularEstatisticas(float soma[][NUM_GRANDEZAS],
                           int cont[][NUM_GRANDEZAS],
                           float min[],
                           float max[]) {

    for (int i = 0; i < qtdMed; i++) {

        int eqIndex = buscarEquipamento(medicoes[i].idEq);
        int gIndex = indiceGrandeza(medicoes[i].grandeza);

        soma[eqIndex][gIndex] += medicoes[i].valor;
        cont[eqIndex][gIndex]++;

        if (medicoes[i].valor < min[gIndex])
            min[gIndex] = medicoes[i].valor;

        if (medicoes[i].valor > max[gIndex])
            max[gIndex] = medicoes[i].valor;
    }
}

void exibirRelatorio(float soma[][NUM_GRANDEZAS],
                     int cont[][NUM_GRANDEZAS],
                     float min[],
                     float max[]) {

    char letras[NUM_GRANDEZAS] = {'V','I','P','T'};

    printf("\n===== MEDIAS =====\n");

    for (int i = 0; i < qtdEq; i++) {
        printf("\nEquipamento %d (%s)\n",
               equipamentos[i].id,
               equipamentos[i].nome);

        for (int j = 0; j < NUM_GRANDEZAS; j++)
            if (cont[i][j] > 0)
                printf("%c: %.2f\n",
                       letras[j],
                       soma[i][j] / cont[i][j]);
    }

    printf("\n===== MIN E MAX =====\n");

    for (int i = 0; i < NUM_GRANDEZAS; i++)
        if (min[i] != FLT_MAX)
            printf("%c -> Min: %.2f | Max: %.2f\n",
                   letras[i],
                   min[i],
                   max[i]);
}

void relatorios() {

    if (qtdMed == 0) {
        printf("\nSem medicoes.\n");
        return;
    }

    float soma[MAX_EQ][NUM_GRANDEZAS] = {0};
    int cont[MAX_EQ][NUM_GRANDEZAS] = {0};
    float min[NUM_GRANDEZAS];
    float max[NUM_GRANDEZAS];

    for (int i = 0; i < NUM_GRANDEZAS; i++) {
        min[i] = FLT_MAX;
        max[i] = -FLT_MAX;
    }

    calcularEstatisticas(soma, cont, min, max);
    exibirRelatorio(soma, cont, min, max);
}

/* ================= MENU ================= */

void menu() {

    int op;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar\n");
        printf("2 - Registrar\n");
        printf("3 - Listar Equipamentos\n");
        printf("4 - Listar Medicoes\n");
        printf("5 - Relatorios\n");
        printf("6 - Sair\n");
        printf("Opcao: ");

        if (scanf("%d", &op) != 1) {
            printf("Entrada invalida.\n");
            limparBuffer();
            continue;
        }

        switch (op) {
            case 1: cadastrarEquipamento(); break;
            case 2: registrarMedicao(); break;
            case 3: listarEquipamentos(); break;
            case 4: listarMedicoes(); break;
            case 5: relatorios(); break;
            case 6: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida.\n");
        }

    } while (op != 6);
}

/* ================= MAIN ================= */

int main() {
    menu();
    return 0;
}
