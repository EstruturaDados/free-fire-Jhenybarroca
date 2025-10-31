/*
 * DESAFIO NÍVEL 2: VETOR vs. LISTA ENCADEADA
 * Descrição: Este programa implementa um sistema de inventário usando
 * duas estruturas de dados (Vetor e Lista Encadeada) para comparar
 * suas operações e eficiência, especialmente em buscas.
 *
 * Requisitos:
 * - Structs Item e No.
 * - Implementações paralelas (Vetor, Lista).
 * - Funções CRUD (Inserir, Remover, Listar, Buscar Seq.) para ambas.
 * - Funções de Ordenação (Selection Sort) e Busca Binária para o Vetor.
 * - Contador de comparações para as buscas.
 */

// --- 1. Bibliotecas Necessárias (Instrução) ---
#include <stdio.h>
#include <stdlib.h>   // Para alocação dinâmica (malloc, free) e system()
#include <string.h>   // Para manipulação de strings (strcmp, strcpy, strcspn)
// time.h não será usado, pois o foco é o contador de operações (Req. 6)

// --- 2. Constantes e Definições de Structs ---

// Tamanho máximo da mochila (Vetor)
#define TAM_MOCHILA 10

/**
 * @brief (Requisito 1: Struct Item)
 * Define a estrutura de dados para um item coletado.
 */
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

/**
 * @brief (Requisito 1: Struct No)
 * Define o nó da lista encadeada.
 * Contém o 'Item' e um ponteiro para o próximo nó.
 */
struct No {
    struct Item dados;
    struct No* proximo;
};

// --- 3. Variáveis Globais (Estado do Sistema) ---

// Abordagem 1: Vetor (Lista Sequencial)
struct Item mochilaVetor[TAM_MOCHILA];
int totalVetor = 0;        // Controla o número de itens no vetor
int vetorOrdenado = 0;     // Flag: 0 = Não, 1 = Sim (Req. 5)

// Abordagem 2: Lista Encadeada
// 'listaInicio' é o ponteiro de cabeça (head) da lista
struct No* listaInicio = NULL;

// Contador de operações (Requisito 6)
int contadorComparacoes = 0;

// --- 4. Protótipos de Funções (Modularização) ---

// Funções de Utilidade (RNF: Usabilidade)
void limparBuffer();
void pausarSistema();
void limparTela();

// Menus (RNF: Usabilidade)
void menuPrincipal();
void menuVetor();
void menuLista();

// Funções do VETOR (Requisito 2)
void inserirItemVetor();
void removerItemVetor();
void listarItensVetor();
void ordenarVetor();           // Requisito 4
void buscarSequencialVetor();  // Requisito 3
void buscarBinariaVetor();     // Requisito 5

// Funções da LISTA ENCADEADA (Requisito 2)
void inserirItemLista();
void removerItemLista();
void listarItensLista();
void buscarSequencialLista();  // Requisito 3
void liberarLista();           // Boa prática de gerenciamento de memória

// --- 5. Função Principal (Main) ---

int main() {
    menuPrincipal();
    liberarLista(); // Limpa a memória alocada pela lista ao sair
    return 0;
}

// --- 6. Implementação dos Menus (RNF: Usabilidade) ---

/**
 * @brief Menu principal para selecionar a estrutura de dados.
 */
void menuPrincipal() {
    int opcao;
    do {
        limparTela();
        printf("=======================================\n");
        printf("  COMPARATIVO DE ESTRUTURAS DE DADOS\n");
        printf("=======================================\n");
        printf("Escolha como gerenciar a mochila:\n\n");
        printf("1. Mochila (Vetor / Lista Sequencial)\n");
        printf("2. Mochila (Lista Encadeada)\n");
        printf("0. Sair do Jogo\n");
        printf("---------------------------------------\n");
        printf("Opcao: ");
        
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                pausarSistema();
        }
    } while (opcao != 0);
}

/**
 * @brief Submenu para operações no VETOR.
 */
void menuVetor() {
    int opcao;
    do {
        limparTela();
        printf("--- Mochila (VETOR) [%d/%d] ---\n", totalVetor, TAM_MOCHILA);
        printf("Status: %s\n", vetorOrdenado ? "Ordenado" : "Nao Ordenado");
        printf("---------------------------------------\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Ordenar Vetor (Selection Sort)\n");
        printf("5. Buscar Item (Sequencial)\n");
        printf("6. Buscar Item (Binaria) %s\n", (vetorOrdenado ? "" : "(Vetor precisa estar ordenado)"));
        printf("0. Voltar ao Menu Principal\n");
        printf("---------------------------------------\n");
        printf("Opcao: ");
        
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarItensVetor(); break;
            case 4: ordenarVetor(); break;
            case 5: buscarSequencialVetor(); break;
            case 6: buscarBinariaVetor(); break;
            case 0: break; // Volta ao menu anterior
            default: printf("\nOpcao invalida!\n");
        }
        if (opcao != 0) pausarSistema();
    } while (opcao != 0);
}

/**
 * @brief Submenu para operações na LISTA ENCADEADA.
 */
void menuLista() {
    int opcao;
    do {
        limparTela();
        printf("--- Mochila (LISTA ENCADEADA) ---\n");
        printf("---------------------------------------\n");
        printf("1. Adicionar Item (no inicio)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item (Sequencial)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("---------------------------------------\n");
        printf("Opcao: ");
        
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarItensLista(); break;
            case 4: buscarSequencialLista(); break;
            case 0: break; // Volta ao menu anterior
            default: printf("\nOpcao invalida!\n");
        }
        if (opcao != 0) pausarSistema();
    } while (opcao != 0);
}

// --- 7. Implementação das Funções do VETOR ---

/**
 * @brief (Req 3: Inserir) Adiciona um item ao vetor.
 * A inserção desordena o vetor.
 */
void inserirItemVetor() {
    if (totalVetor >= TAM_MOCHILA) {
        printf("\n[ERRO] Mochila (Vetor) cheia!\n");
        return;
    }

    struct Item novoItem;
    printf("Nome do item: ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0;

    printf("Tipo do item: ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBuffer();

    mochilaVetor[totalVetor] = novoItem;
    totalVetor++;
    
    vetorOrdenado = 0; // Inserção quebra a ordenação
    printf("\n[SUCESSO] Item '%s' adicionado ao vetor.\n", novoItem.nome);
}

/**
 * @brief (Req 3: Listar) Exibe todos os itens do vetor.
 */
void listarItensVetor() {
    printf("\n--- Itens no Vetor (%d/%d) ---\n", totalVetor, TAM_MOCHILA);
    if (totalVetor == 0) {
        printf("Mochila (Vetor) vazia.\n");
        return;
    }
    for (int i = 0; i < totalVetor; i++) {
        printf("------------------------\n");
        printf(" Slot %d (Nome: %s | Tipo: %s | Qtd: %d)\n",
               i, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

/**
 * @brief (Req 4: Ordenar) Ordena o vetor por nome usando Selection Sort.
 * Documentação: Selection Sort é eficiente para listas pequenas.
 * Encontra o menor item e o troca com a posição atual.
 */
void ordenarVetor() {
    if (totalVetor == 0) {
        printf("\nImpossivel ordenar: mochila vazia.\n");
        return;
    }

    for (int i = 0; i < totalVetor - 1; i++) {
        int min_idx = i;
        // Encontra o índice do menor item no restante do vetor
        for (int j = i + 1; j < totalVetor; j++) {
            // Compara os nomes
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[min_idx].nome) < 0) {
                min_idx = j;
            }
        }
        // Troca o item atual (i) com o menor encontrado (min_idx)
        if (min_idx != i) {
            struct Item temp = mochilaVetor[i];
            mochilaVetor[i] = mochilaVetor[min_idx];
            mochilaVetor[min_idx] = temp;
        }
    }
    
    vetorOrdenado = 1; // Atualiza a flag
    printf("\n[SUCESSO] Vetor ordenado por nome (Selection Sort).\n");
    listarItensVetor();
}

/**
 * @brief (Req 3: Buscar) Busca sequencial no vetor.
 * Documentação: Percorre o vetor 1 a 1.
 * O(N) no pior caso.
 */
void buscarSequencialVetor() {
    if (totalVetor == 0) {
        printf("\nMochila (Vetor) vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("Nome do item a buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    contadorComparacoes = 0; // (Req 6: Contador)
    int encontrado = 0;

    for (int i = 0; i < totalVetor; i++) {
        contadorComparacoes++; // Incrementa a cada comparação
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            printf("\n[ENCONTRADO - Busca Sequencial]\n");
            printf("Nome: %s | Tipo: %s | Qtd: %d\n",
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n[NAO ENCONTRADO] Item '%s'.\n", nomeBusca);
    }
    printf("-> Total de Comparacoes: %d\n", contadorComparacoes);
}

/**
 * @brief (Req 5: Busca Binária) Busca binária no vetor.
 * Documentação: Requer vetor ordenado. Divide o vetor pela metade
 * a cada passo. O(log N) no pior caso.
 */
void buscarBinariaVetor() {
    if (!vetorOrdenado) {
        printf("\n[ERRO] A busca binaria exige que o vetor esteja ordenado!\n");
        printf("Use a opcao 4 para ordenar.\n");
        return;
    }
    if (totalVetor == 0) {
        printf("\nMochila (Vetor) vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("Nome do item a buscar (Busca Binaria): ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    contadorComparacoes = 0; // (Req 6: Contador)
    int inicio = 0;
    int fim = totalVetor - 1;
    int encontrado = 0;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2; // Evita overflow de (inicio+fim)/2
        
        contadorComparacoes++; // (Req 6: Contador)
        int cmp = strcmp(nomeBusca, mochilaVetor[meio].nome);

        if (cmp == 0) { // Encontrado
            printf("\n[ENCONTRADO - Busca Binaria]\n");
            printf("Nome: %s | Tipo: %s | Qtd: %d\n",
                   mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            encontrado = 1;
            break;
        } else if (cmp < 0) { // Item buscado é menor (vem antes)
            fim = meio - 1;
        } else { // Item buscado é maior (vem depois)
            inicio = meio + 1;
        }
    }

    if (!encontrado) {
        printf("\n[NAO ENCONTRADO] Item '%s'.\n", nomeBusca);
    }
    printf("-> Total de Comparacoes: %d\n", contadorComparacoes);
}

/**
 * @brief (Req 3: Remover) Remove um item do vetor.
 * Documentação: A remoção em vetor exige deslocamento (shift)
 * dos elementos posteriores. O(N) no pior caso.
 */
void removerItemVetor() {
    if (totalVetor == 0) {
        printf("\nMochila (Vetor) vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("Nome do item a remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    int index = -1;
    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\n[ERRO] Item '%s' nao encontrado para remocao.\n", nomeBusca);
        return;
    }

    // Desloca (shift) os elementos para a esquerda
    for (int i = index; i < totalVetor - 1; i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }
    
    totalVetor--;
    vetorOrdenado = 0; // Remoção pode quebrar a ordenação
    printf("\n[SUCESSO] Item '%s' removido do vetor.\n", nomeBusca);
}

// --- 8. Implementação das Funções da LISTA ENCADEADA ---

/**
 * @brief (Req 3: Inserir) Insere um item na lista.
 * Documentação: A inserção ocorre no início da lista.
 * Esta é uma operação O(1) (tempo constante).
 */
void inserirItemLista() {
    // 1. Aloca memória para o novo nó
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    if (novoNo == NULL) {
        printf("\n[ERRO FATAL] Falha ao alocar memoria (malloc)!\n");
        return;
    }

    // 2. Coleta os dados do item
    printf("Nome do item: ");
    fgets(novoNo->dados.nome, 30, stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = 0;

    printf("Tipo do item: ");
    fgets(novoNo->dados.tipo, 20, stdin);
    novoNo->dados.tipo[strcspn(novoNo->dados.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    limparBuffer();

    // 3. Insere no início da lista
    novoNo->proximo = listaInicio;
    listaInicio = novoNo;

    printf("\n[SUCESSO] Item '%s' adicionado a lista.\n", novoNo->dados.nome);
}

/**
 * @brief (Req 3: Listar) Exibe todos os itens da lista.
 * Documentação: Percorre a lista nó a nó, do início (head) ao fim.
 */
void listarItensLista() {
    printf("\n--- Itens na Lista Encadeada ---\n");
    if (listaInicio == NULL) {
        printf("Mochila (Lista) vazia.\n");
        return;
    }

    struct No* atual = listaInicio;
    int i = 1;
    while (atual != NULL) {
        printf("------------------------\n");
        printf(" No %d (Nome: %s | Tipo: %s | Qtd: %d)\n",
               i, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
        i++;
    }
}

/**
 * @brief (Req 3: Buscar) Busca sequencial na lista.
 * Documentação: Percorre a lista nó a nó.
 * O(N) no pior caso.
 */
void buscarSequencialLista() {
    if (listaInicio == NULL) {
        printf("\nMochila (Lista) vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("Nome do item a buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    contadorComparacoes = 0; // (Req 6: Contador)
    struct No* atual = listaInicio;
    int encontrado = 0;

    while (atual != NULL) {
        contadorComparacoes++; // Incrementa a cada comparação
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("\n[ENCONTRADO - Busca Sequencial]\n");
            printf("Nome: %s | Tipo: %s | Qtd: %d\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("\n[NAO ENCONTRADO] Item '%s'.\n", nomeBusca);
    }
    printf("-> Total de Comparacoes: %d\n", contadorComparacoes);
}

/**
 * @brief (Req 3: Remover) Remove um item da lista.
 * Documentação: Requer dois ponteiros (atual e anterior)
 * para "religar" a lista após a remoção. O(N) para buscar, O(1) para remover.
 */
void removerItemLista() {
    if (listaInicio == NULL) {
        printf("\nMochila (Lista) vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("Nome do item a remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    struct No* atual = listaInicio;
    struct No* anterior = NULL;

    // Procura o nó
    while (atual != NULL && strcmp(atual->dados.nome, nomeBusca) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Se atual == NULL, o item não foi encontrado
    if (atual == NULL) {
        printf("\n[ERRO] Item '%s' nao encontrado para remocao.\n", nomeBusca);
        return;
    }

    // Caso 1: O item a remover é o primeiro (listaInicio)
    if (anterior == NULL) {
        listaInicio = atual->proximo;
    }
    // Caso 2: O item está no meio ou fim
    else {
        anterior->proximo = atual->proximo;
    }

    // Libera a memória do nó removido
    free(atual);
    printf("\n[SUCESSO] Item '%s' removido da lista.\n", nomeBusca);
}

/**
 * @brief Libera toda a memória alocada dinamicamente pela lista.
 */
void liberarLista() {
    struct No* atual = listaInicio;
    while (atual != NULL) {
        struct No* temp = atual; // Guarda o nó atual
        atual = atual->proximo;  // Avança para o próximo
        free(temp);              // Libera o nó guardado
    }
    listaInicio = NULL;
}


// --- 9. Implementação das Funções de Utilidade ---

/**
 * @brief Limpa o buffer de entrada (stdin).
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Pausa a execução e aguarda o usuário pressionar Enter.
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

