# Sistema de Cadastro de Equipamentos e Medições Elétricas
Este repositório contém um programa desenvolvido em linguagem C para cadastro de equipamentos e registro de medições elétricas.  

O sistema funciona totalmente via terminal, utilizando entrada e saída padrão (printf e scanf), com armazenamento em memória por meio de struct, vetores e matriz de resumo.  

## Pré-requisitos
Antes de executar o projeto, verifique se você possui:

✅ GCC (GNU Compiler Collection) instalado

✅ Terminal (Linux, macOS ou Windows com MinGW ou WSL)

Versão mínima recomendada do compilador:

✅ C99 ou superior

Você pode verificar sua versão com:

```bash
gcc --version
```

## Passo 1️⃣: Baixar o arquivo
Coloque o arquivo .c do projeto em uma pasta local no seu computador.  
Exemplo:  

```bash
projeto/
│
└── ELE_nome_sobrenome.c
```

## Passo 2️⃣: Compilar o programa
Abra o terminal na pasta onde está o arquivo .c e execute:  

```bash
gcc ELE_nome_sobrenome.c -o programa
```
Isso irá gerar um arquivo executável chamado programa.  

## Passo 3️⃣: Executar o programa
No Linux, macOS e Windows:  

```bash
./programa
```
O menu principal será exibido no terminal.  

## Estrutura Geral do Sistema
O programa é dividido logicamente nas seguintes partes:  

• Modelo de dados  
• Armazenamento em memória  
• Funções auxiliares  
• Cadastro  
• Registro de medições  
• Listagem  
• Relatórios  
• Controle de fluxo (menu)  
• Função principal  

## Explicação das Funcionalidades

## 1. Cadastro de Equipamentos  
Permite cadastrar um novo equipamento no sistema.  
O usuário informa:  

• ID (inteiro)  
• Nome  
• Tipo  

Validações implementadas:  

• Não permite ID duplicado  
• Limite máximo de equipamentos definido por MAX_EQ  
• Dados armazenados em vetor de struct Equipamento  

Exemplo de uso:  

```bash
1 - Cadastrar equipamento
ID: 1
Nome: Motor
Tipo: Inducao
```

## 2. Registro de Medições  
Permite registrar uma medição vinculada a um equipamento existente.  

O usuário informa:  

• ID do equipamento  
• Grandeza (V, I, P ou T)  
• Valor (float)  

Validações:

• Não permite registrar medição para equipamento inexistente  
• Não permite grandeza inválida  
• Aceita letra minúscula ou maiúscula  

Exemplo:  

```bash
2 - Registrar medicao
ID: 1
Grandeza: V
Valor: 220
```

## 3. Listagem de Equipamentos  

Exibe todos os equipamentos cadastrados em formato de tabela:  

```bash
ID        Nome                 Tipo
1         Motor                Inducao
```
A saída utiliza formatação alinhada para melhor visualização.  

## 4. Listagem de Medições  
Exibe todas as medições registradas:  

```bash
ID Eq     Grandeza   Valor
1         V          220.00
```
Os valores são exibidos com duas casas decimais.  

## 5. Relatórios
O sistema gera dois tipos de relatório:  
• Médias por Equipamento e por Grandeza  
Internamente utiliza matriz:  

```bash
float soma[MAX_EQ][4]
int cont[MAX_EQ][4]
```

Cada linha representa um equipamento.  
Cada coluna representa uma grandeza:  

0 → V  
1 → I  
2 → P  
3 → T  
Cálculo da média:  

```bash
média = soma / contagem
```

• Mínimo e Máximo por Grandeza  

Para cada grandeza registrada, o sistema calcula:  
Menor valor registrado  
Maior valor registrado  

Exemplo de saída:  

```bash
V -> Min: 220.00 | Max: 230.00
```

## 6. Encerramento  
A opção "Sair" encerra o programa.  

Observação importante:  
Todos os dados são mantidos apenas durante a execução.  
Ao encerrar o programa, os dados são perdidos.  

## Estruturas de Dados Utilizadas  

struct Equipamento  

```bash
int id
char nome[60]
char tipo[30]
```

struct Medicao  

```bash
int idEq
char grandeza
float valor
```

## Limitações do Sistema  

• Dados não persistem após encerramento  
• Limite máximo fixo de equipamentos e medições  
• Validação básica de entrada  

## Exemplo Completo de Execução  

```bash
1
1
Motor
Inducao

2
1
V
220

5

```

Saída esperada:  

```bash
Equipamento 1 (Motor):
V: 220.00

V -> Min: 220.00 | Max: 220.00
```

Aproveite o projeto.
