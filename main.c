/*
Aluno: Cauã Barcelos Corrêa
Curso: Engenharia Eletrica - Programacao I
Turma 6.2
UFES
Trabalho Computacional
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EQ 100
#define MAX_MED 500

/* ================= MODELO DE DADOS ================= */

typedef struct
{
    int id;
    char nome[60];
    char tipo[30];
} Equipamento;

typedef struct
{
    int idEq;
    char grandeza; // 'V', 'I', 'P', 'T'
    float valor;
} Medicao;

/* ================= ARMAZENAMENTO EM MEMÓRIA ================= */

Equipamento equipamentos[MAX_EQ];
Medicao medicoes[MAX_MED];

int qtdEq = 0;
int qtdMed = 0;

/* ================= FUNÇÕES AUXILIARES ================= */

int buscarEquipamento(int id)
{
    for (int i = 0; i < qtdEq; i++)
    {
        if (equipamentos[i].id == id)
            return i;
    }
    return -1;
}

int indiceGrandeza(char g)
{
    if (g == 'V')
        return 0;
    if (g == 'I')
        return 1;
    if (g == 'P')
        return 2;
    if (g == 'T')
        return 3;
    return -1;
}

/* ================= CADASTRO ================= */

void cadastrarEquipamento()
{
    if (qtdEq >= MAX_EQ)
    {
        printf("\nLimite de equipamentos atingido!\n");
        return;
    }

    int id;
    printf("\nID do equipamento: ");
    scanf("%d", &id);

    if (buscarEquipamento(id) != -1)
    {
        printf("Erro: ID ja existente!\n");
        return;
    }

    equipamentos[qtdEq].id = id;

    printf("Nome: ");
    scanf(" %[^\n]", equipamentos[qtdEq].nome);

    printf("Tipo: ");
    scanf(" %[^\n]", equipamentos[qtdEq].tipo);

    qtdEq++;

    printf("Equipamento cadastrado com sucesso!\n");
}

/* ================= REGISTRO DE MEDIÇÕES ================= */

void registrarMedicao()
{
    if (qtdMed >= MAX_MED)
    {
        printf("\nLimite de medicoes atingido!\n");
        return;
    }

    int id;
    printf("\nID do equipamento: ");
    scanf("%d", &id);

    int pos = buscarEquipamento(id);
    if (pos == -1)
    {
        printf("Erro: equipamento nao encontrado!\n");
        return;
    }

    char g;
    printf("Grandeza (V/I/P/T): ");
    scanf(" %c", &g);

    g = toupper(g);

    int gIndex = indiceGrandeza(g);
    if (gIndex == -1)
    {
        printf("Erro: grandeza invalida!\n");
        return;
    }

    float valor;
    printf("Valor: ");
    scanf("%f", &valor);

    medicoes[qtdMed].idEq = id;
    medicoes[qtdMed].grandeza = g;
    medicoes[qtdMed].valor = valor;

    qtdMed++;

    printf("Medicao registrada com sucesso!\n");
}

/* ================= LISTAGEM ================= */

void listarEquipamentos()
{
    if (qtdEq == 0)
    {
        printf("\nNenhum equipamento cadastrado.\n");
        return;
    }

    printf("\n===== LISTA DE EQUIPAMENTOS =====\n");
    printf("%-10s %-20s %-20s\n", "ID", "Nome", "Tipo");

    for (int i = 0; i < qtdEq; i++)
    {
        printf("%-10d %-20s %-20s\n",
               equipamentos[i].id,
               equipamentos[i].nome,
               equipamentos[i].tipo);
    }
}

void listarMedicoes()
{
    if (qtdMed == 0)
    {
        printf("\nNenhuma medicao registrada.\n");
        return;
    }

    printf("\n===== LISTA DE MEDICOES =====\n");
    printf("%-10s %-10s %-10s\n", "ID Eq", "Grandeza", "Valor");

    for (int i = 0; i < qtdMed; i++)
    {
        printf("%-10d %-10c %-10.2f\n",
               medicoes[i].idEq,
               medicoes[i].grandeza,
               medicoes[i].valor);
    }
}

/* ================= RELATÓRIOS ================= */

void relatorios()
{
    if (qtdMed == 0)
    {
        printf("\nNao ha medicoes para gerar relatorio.\n");
        return;
    }

    float soma[MAX_EQ][4] = {0};
    int cont[MAX_EQ][4] = {0};

    float min[4] = {999999, 999999, 999999, 999999};
    float max[4] = {-999999, -999999, -999999, -999999};

    for (int i = 0; i < qtdMed; i++)
    {
        int eqIndex = buscarEquipamento(medicoes[i].idEq);
        if (eqIndex == -1)
            continue;

        int gIndex = indiceGrandeza(medicoes[i].grandeza);

        soma[eqIndex][gIndex] += medicoes[i].valor;
        cont[eqIndex][gIndex]++;

        if (medicoes[i].valor < min[gIndex])
            min[gIndex] = medicoes[i].valor;

        if (medicoes[i].valor > max[gIndex])
            max[gIndex] = medicoes[i].valor;
    }

    char letras[4] = {'V', 'I', 'P', 'T'};

    printf("\n===== MEDIAS POR EQUIPAMENTO =====\n");

    for (int i = 0; i < qtdEq; i++)
    {
        printf("\nEquipamento %d (%s):\n",
               equipamentos[i].id,
               equipamentos[i].nome);

        for (int j = 0; j < 4; j++)
        {
            if (cont[i][j] > 0)
            {
                printf("%c: %.2f\n",
                       letras[j],
                       soma[i][j] / cont[i][j]);
            }
        }
    }

    printf("\n===== MINIMO E MAXIMO POR GRANDEZA =====\n");

    for (int i = 0; i < 4; i++)
    {
        if (min[i] != 999999)
        {
            printf("%c -> Min: %.2f | Max: %.2f\n",
                   letras[i],
                   min[i],
                   max[i]);
        }
    }
}

/* ================= MENU ================= */

void menu()
{
    int op;

    do
    {
        printf("\n========= MENU =========\n");
        printf("1 - Cadastrar equipamento\n");
        printf("2 - Registrar medicao\n");
        printf("3 - Listar equipamentos\n");
        printf("4 - Listar medicoes\n");
        printf("5 - Relatorios\n");
        printf("6 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            cadastrarEquipamento();
            break;
        case 2:
            registrarMedicao();
            break;
        case 3:
            listarEquipamentos();
            break;
        case 4:
            listarMedicoes();
            break;
        case 5:
            relatorios();
            break;
        case 6:
            printf("Encerrando...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }

    } while (op != 6);
}

/* ================= MAIN ================= */

int main()
{
    menu();
    return 0;
}
