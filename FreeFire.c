/*
 * DESAFIO FINAL: A TORRE DE RESGATE
 * Descrição: Sistema para gerenciar componentes da torre de fuga,
 * permitindo ordenação por diferentes critérios (Bubble, Insertion,
 * Selection Sort) e medindo o desempenho (comparações e tempo)
 * de cada algoritmo. Inclui busca binária pós-ordenação.
 *
 * Requisitos:
 * - Struct Componente (nome, tipo, prioridade)
 * - Vetor de 20 componentes
 * - Bubble Sort (por nome)
 * - Insertion Sort (por tipo)
 * - Selection Sort (por prioridade)
 * - Busca Binária (por nome)
 * - Métricas: Contagem de comparações e tempo (clock())
 */

// --- 1. Bibliotecas Necessárias ---
#include <stdio.h>
#include <stdlib.h>     // Para system()
#include <string.h>     // Para strcmp(), strcpy(), strcspn()
#include <time.h>       // Para clock() (FR.5)

// --- 2. Structs e Constantes (FR.1) ---
#define MAX_COMPONENTES 20

/**
 * @brief (FR.1) Define a estrutura de um componente
 * para a torre de resgate.
 */
struct Componente {
    char nome[30];
    char tipo[20];
    int prioridade; // 1 a 10
};

// --- 3. Variáveis Globais (Estado do Sistema) ---

// Vetor principal que armazena os componentes
struct Componente torre[MAX_COMPONENTES];
// Cópia de backup para restaurar a ordem original
struct Componente torreBackup[MAX_COMPONENTES]; 

int totalComponentes = 0;

/*
 * Flag para controlar o estado da ordenação do vetor 'torre':
 * 0 = Nao ordenado (ou estado original)
 * 1 = Ordenado por NOME
 * 2 = Ordenado por TIPO
 * 3 = Ordenado por PRIORIDADE
 */
int estadoOrdenacao = 0;

// Variáveis para métricas de desempenho (FR.5)
long long int contadorComparacoes = 0; // 'long long' para seguranca
double tempoExecucao = 0.0;

// --- 4. Protótipos de Funções ---

// Funções de Utilidade (NFR: Interface e Clareza)
void limparBuffer();
void pausarSistema();
void limparTela();
void restaurarBackup(); // Restaura 'torre' a partir de 'torreBackup'

// Funções Principais (Requisitos Funcionais)
void cadastrarComponente();     // FR.2
void mostrarComponentes(const char* titulo); // FR.6
void bubbleSortNome();          // FR.3
void insertionSortTipo();       // FR.3
void selectionSortPrioridade(); // FR.3
void buscaBinariaPorNome();     // FR.4

// --- 5. Função Principal (Menu - NFR.1) ---
int main() {
    int opcao;

    do {
        limparTela();
        printf("========================================\n");
        printf("    TORRE DE RESGATE (DESAFIO FINAL)    \n");
        printf("========================================\n");
        printf("Componentes na base: %d / %d\n", totalComponentes, MAX_COMPONENTES);
        printf("Estado atual: ");
        switch(estadoOrdenacao) {
            case 0: printf("Original (Nao Ordenado)\n"); break;
            case 1: printf("Ordenado por Nome\n"); break;
            case 2: printf("Ordenado por Tipo\n"); break;
            case 3: printf("Ordenado por Prioridade\n"); break;
        }
        printf("----------------------------------------\n");
        printf("1. Cadastrar Componente\n");
        printf("2. Listar Componentes (Estado Atual)\n");
        printf("3. Restaurar Ordem Original de Cadastro\n");
        printf("----------------------------------------\n");
        printf("   Escolha a Estrategia de Ordenacao:\n");
        printf("4. Ordenar por NOME (Bubble Sort)\n");
        printf("5. Ordenar por TIPO (Insertion Sort)\n");
        printf("6. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("----------------------------------------\n");
        printf("7. Buscar Componente-Chave (Busca Binaria)\n");
        printf("0. Sair\n");
        printf("----------------------------------------\n");
        printf("Escolha sua acao: ");
        
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: cadastrarComponente(); break;
            case 2:
                mostrarComponentes("Listagem Atual dos Componentes");
                break;
            case 3: restaurarBackup(); break;
            case 4: bubbleSortNome(); break;
            case 5: insertionSortTipo(); break;
            case 6: selectionSortPrioridade(); break;
            case 7: buscaBinariaPorNome(); break;
            case 0: printf("\nSaindo do simulador...\n"); break;
            default: printf("\nOpcao invalida! Tente novamente.\n");
        }
        
        if(opcao != 0) pausarSistema();

    } while (opcao != 0);

    return 0;
}

// --- 6. Implementação das Funções Principais ---

/**
 * @brief (FR.2) Cadastra um novo componente no vetor 'torre'.
 * Também salva no 'torreBackup' e redefine o estado de ordenação.
 */
void cadastrarComponente() {
    limparTela();
    printf("--- 1. Cadastrar Novo Componente ---\n");
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("[ERRO] A base da torre esta cheia (Max: %d).\n", MAX_COMPONENTES);
        return;
    }

    // Coleta dados
    struct Componente novo;
    printf("Nome (ex: Chip Central): ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0; // Remove '\n'

    printf("Tipo (ex: Controle, Suporte, Propulsao): ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0; // Remove '\n'

    printf("Prioridade (1-10): ");
    scanf("%d", &novo.prioridade);
    limparBuffer();

    // Adiciona ao vetor principal e ao backup
    torre[totalComponentes] = novo;
    torreBackup[totalComponentes] = novo;
    totalComponentes++;

    estadoOrdenacao = 0; // Cadastro "desordena" a lista
    printf("\n[SUCESSO] Componente '%s' adicionado.\n", novo.nome);
}

/**
 * @brief (FR.6) Exibe todos os componentes no estado atual.
 * @param titulo Um cabeçalho para a listagem.
 */
void mostrarComponentes(const char* titulo) {
    limparTela();
    printf("--- %s ---\n", titulo);
    if (totalComponentes == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }

    // Cabeçalho da tabela
    printf("-------------------------------------------------------------\n");
    printf("| %-20s | %-15s | %-10s |\n", "NOME", "TIPO", "PRIORIDADE");
    printf("-------------------------------------------------------------\n");

    // Dados (NFR: Clareza)
    for (int i = 0; i < totalComponentes; i++) {
        printf("| %-20s | %-15s | %-10d |\n",
               torre[i].nome,
               torre[i].tipo,
               torre[i].prioridade);
    }
    printf("-------------------------------------------------------------\n");
}

/**
 * @brief Restaura o vetor 'torre' ao estado original (backup).
 * (NFR: Usabilidade)
 */
void restaurarBackup() {
    if (totalComponentes == 0) {
        printf("\nNenhum componente para restaurar.\n");
        return;
    }
    
    // Copia os dados do backup de volta para o vetor principal
    for(int i = 0; i < totalComponentes; i++) {
        torre[i] = torreBackup[i];
    }
    
    estadoOrdenacao = 0; // Reseta o estado
    printf("\n[SUCESSO] Ordem original de cadastro restaurada.\n");
    mostrarComponentes("Listagem Apos Restauracao");
}


/**
 * @brief (FR.3) Ordena 'torre' por NOME usando Bubble Sort.
 * Mede comparações e tempo de execução (FR.5).
 */
void bubbleSortNome() {
    if (totalComponentes == 0) {
        printf("\nNenhum componente para ordenar.\n");
        return;
    }
    
    // Restaura o backup para garantir uma medição justa
    restaurarBackup();
    pausarSistema(); // Pausa para o usuário ver a lista restaurada

    printf("\nIniciando Ordenacao por NOME (Bubble Sort)...\n");

    // --- Início Medição (FR.5) ---
    contadorComparacoes = 0;
    clock_t inicio = clock();

    struct Componente temp;
    for (int i = 0; i < totalComponentes - 1; i++) {
        for (int j = 0; j < totalComponentes - 1 - i; j++) {
            
            contadorComparacoes++; // (FR.5) Conta a comparação
            
            // Compara os nomes (string.h)
            if (strcmp(torre[j].nome, torre[j+1].nome) > 0) {
                // Troca
                temp = torre[j];
                torre[j] = torre[j+1];
                torre[j+1] = temp;
            }
        }
    }

    // --- Fim Medição (FR.5) ---
    clock_t fim = clock();
    tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    estadoOrdenacao = 1; // 1 = Ordenado por Nome

    printf("\n[SUCESSO] Ordenacao concluida.\n");
    printf("-> ALGORITMO: Bubble Sort\n");
    printf("-> COMPARacoes: %lld\n", contadorComparacoes); // (NFR.2)
    printf("-> TEMPO: %f segundos\n", tempoExecucao); // (NFR.2)

    mostrarComponentes("Componentes Ordenados por NOME");
}

/**
 * @brief (FR.3) Ordena 'torre' por TIPO usando Insertion Sort.
 * Mede comparações e tempo de execução (FR.5).
 */
void insertionSortTipo() {
    if (totalComponentes == 0) {
        printf("\nNenhum componente para ordenar.\n");
        return;
    }

    restaurarBackup();
    pausarSistema();

    printf("\nIniciando Ordenacao por TIPO (Insertion Sort)...\n");

    // --- Início Medição (FR.5) ---
    contadorComparacoes = 0;
    clock_t inicio = clock();

    for (int i = 1; i < totalComponentes; i++) {
        struct Componente chave = torre[i];
        int j = i - 1;

        /* Move os elementos de torre[0..i-1], que são maiores
           que a chave, uma posição à frente */
        while (j >= 0) {
            contadorComparacoes++; // (FR.5)
            if (strcmp(torre[j].tipo, chave.tipo) > 0) {
                torre[j+1] = torre[j];
                j = j - 1;
            } else {
                break; // Encontrou a posição correta
            }
        }
        // (Nota: Em uma implementação pura, o 'while' teria a comparação
        // e contaria mesmo ao falhar. Esta forma é mais didática.)
        
        torre[j+1] = chave;
    }

    // --- Fim Medição (FR.5) ---
    clock_t fim = clock();
    tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    estadoOrdenacao = 2; // 2 = Ordenado por Tipo

    printf("\n[SUCESSO] Ordenacao concluida.\n");
    printf("-> ALGORITMO: Insertion Sort\n");
    printf("-> COMPARacoes: %lld\n", contadorComparacoes);
    printf("-> TEMPO: %f segundos\n", tempoExecucao);

    mostrarComponentes("Componentes Ordenados por TIPO");
}

/**
 * @brief (FR.3) Ordena 'torre' por PRIORIDADE (int) usando Selection Sort.
 * Mede comparações e tempo de execução (FR.5).
 */
void selectionSortPrioridade() {
    if (totalComponentes == 0) {
        printf("\nNenhum componente para ordenar.\n");
        return;
    }

    restaurarBackup();
    pausarSistema();

    printf("\nIniciando Ordenacao por PRIORIDADE (Selection Sort)...\n");

    // --- Início Medição (FR.5) ---
    contadorComparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < totalComponentes - 1; i++) {
        // Encontra o índice do item de menor prioridade
        int min_idx = i;
        for (int j = i + 1; j < totalComponentes; j++) {
            
            contadorComparacoes++; // (FR.5)
            
            if (torre[j].prioridade < torre[min_idx].prioridade) {
                min_idx = j;
            }
        }

        // Troca o menor encontrado com o item da posição 'i'
        if (min_idx != i) {
            struct Componente temp = torre[i];
            torre[i] = torre[min_idx];
            torre[min_idx] = temp;
        }
    }

    // --- Fim Medição (FR.5) ---
    clock_t fim = clock();
    tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    estadoOrdenacao = 3; // 3 = Ordenado por Prioridade

    printf("\n[SUCESSO] Ordenacao concluida.\n");
    printf("-> ALGORITMO: Selection Sort\n");
    printf("-> COMPARacoes: %lld\n", contadorComparacoes);
    printf("-> TEMPO: %f segundos\n", tempoExecucao);

    mostrarComponentes("Componentes Ordenados por PRIORIDADE");
}

/**
 * @brief (FR.4) Busca um componente por NOME usando Busca Binária.
 * Só funciona se o vetor estiver ordenado por nome (estado 1).
 */
void buscaBinariaPorNome() {
    limparTela();
    printf("--- 7. Buscar Componente-Chave (Busca Binaria) ---\n");

    // (FR.4) Requisito: Aplicável apenas após ordenação por nome.
    if (estadoOrdenacao != 1) {
        printf("[ERRO] A Busca Binaria por nome exige que a lista\n");
        printf("       esteja ordenada por NOME (Use a Opcao 4).\n");
        return;
    }
    if (totalComponentes == 0) {
        printf("Nenhum componente cadastrado para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do componente-chave: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    int inicio = 0;
    int fim = totalComponentes - 1;
    int encontrado = 0;
    int compBusca = 0; // Contador de comparações da busca

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2; // Evita overflow
        
        compBusca++;
        int cmp = strcmp(nomeBusca, torre[meio].nome);

        if (cmp == 0) { // Encontrou
            printf("\n[SUCESSO] Componente-chave localizado!\n");
            printf("--------------------------------------------------\n");
            printf(" Nome: %s\n", torre[meio].nome);
            printf(" Tipo: %s\n", torre[meio].tipo);
            printf(" Prio: %d\n", torre[meio].prioridade);
            printf("--------------------------------------------------\n");
            encontrado = 1;
            break;
        } else if (cmp < 0) { // O item buscado vem antes (menor)
            fim = meio - 1;
        } else { // O item buscado vem depois (maior)
            inicio = meio + 1;
        }
    }

    if (!encontrado) {
        printf("\n[FALHA] Componente-chave '%s' nao encontrado.\n", nomeBusca);
    }
    
    printf("-> Comparacoes realizadas na busca: %d\n", compBusca);
    // (FR.6) Confirma visualmente a presença (ou ausência).
}


// --- 7. Implementação das Funções de Utilidade ---

/**
 * @brief Limpa o buffer de entrada (stdin).
 * Essencial após scanf() e antes de fgets().
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Pausa a execução e aguarda o usuário pressionar Enter.
 * (NFR: Usabilidade)
 */
void pausarSistema() {
    printf("\nPressione Enter para continuar...");
    limparBuffer();
}

/**
 * @brief Limpa a tela do console (portátil).
 */
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}