#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

#define MAX_EQ 100
#define MAX_MED 500
#define NUM_GRANDEZAS 4

/* ================= MODELO DE DADOS ================= */

struct Equipamento
{
    int id;
    char nome[60];
    char tipo[30];
};

struct Medicao
{
    int idEq;
    char grandeza; // 'V', 'I', 'P', 'T'
    float valor;
};

/* ================= ARMAZENAMENTO EM MEMÓRIA ================= */

struct Equipamento equipamentos[MAX_EQ];
struct Medicao medicoes[MAX_MED];

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
    switch (g)
    {
    case 'V':
        return 0;
    case 'I':
        return 1;
    case 'P':
        return 2;
    case 'T':
        return 3;
    default:
        return -1;
    }
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
    if (scanf("%d", &id) != 1)
    {
        printf("Entrada invalida.\n");
        while (getchar() != '\n')
            ;
        return;
    }

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
    if (scanf("%d", &id) != 1)
    {
        printf("Entrada invalida.\n");
        while (getchar() != '\n')
            ;
        return;
    }

    int eqIndex = buscarEquipamento(id);
    if (eqIndex == -1)
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
    if (scanf("%f", &valor) != 1)
    {
        printf("Entrada invalida.\n");
        while (getchar() != '\n')
            ;
        return;
    }

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

    float soma[MAX_EQ][NUM_GRANDEZAS] = {0};
    int cont[MAX_EQ][NUM_GRANDEZAS] = {0};

    float min[NUM_GRANDEZAS];
    float max[NUM_GRANDEZAS];

    for (int i = 0; i < NUM_GRANDEZAS; i++)
    {
        min[i] = FLT_MAX;
        max[i] = -FLT_MAX;
    }

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

    char letras[NUM_GRANDEZAS] = {'V', 'I', 'P', 'T'};

    printf("\n===== MEDIAS POR EQUIPAMENTO =====\n");

    for (int i = 0; i < qtdEq; i++)
    {

        printf("\nEquipamento %d (%s):\n",
               equipamentos[i].id,
               equipamentos[i].nome);

        for (int j = 0; j < NUM_GRANDEZAS; j++)
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

    for (int i = 0; i < NUM_GRANDEZAS; i++)
    {
        if (min[i] != FLT_MAX)
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

        if (scanf("%d", &op) != 1)
        {
            printf("Entrada invalida.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

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
