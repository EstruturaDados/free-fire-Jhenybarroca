/*
 * DESAFIO NÍVEL 1: MOCHILA DE LOOT
 * Descrição: Este programa simula o inventário inicial (mochila) 
 * de um jogador em um jogo de sobrevivência.
 * * Requisitos:
 * - Struct Item (nome, tipo, quantidade)
 * - Vetor de 10 itens
 * - Funções: inserir, remover, listar, buscar
 * - RNFs: Usabilidade, Documentação, Manutenibilidade
 */

// Bibliotecas necessárias (Instrução)
#include <stdio.h>    // Para entrada e saída (printf, scanf, fgets)
#include <string.h>   // Para manipulação de strings (strcmp, strcspn)
#include <stdlib.h>   // Para limpeza de tela (system)

// --- Definição da Struct e Globais ---

// Constante para o tamanho máximo da mochila
#define TAM_MOCHILA 10

/**
 * @brief (Requisito: Criação da struct)
 * Define a estrutura de dados composta 'Item'.
 * Ela agrega três informações sobre um item coletado.
 */
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Vetor de structs: A mochila em si (Lista Sequencial)
struct Item mochila[TAM_MOCHILA];

// Variável global para controlar o número atual de itens na mochila
int totalItens = 0;

// --- Protótipos das Funções ---

// Funções obrigatórias
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

// Funções auxiliares (Manutenibilidade e Usabilidade)
void limparBuffer();
void limparTela();
void pausarSistema();

// --- Função Principal (Fluxo de Execução) ---

int main() {
    int opcao;

    // O laço 'do-while' garante que o menu seja exibido pelo menos uma vez
    // e continue executando até que o jogador escolha sair (opção 0)
    do {
        limparTela(); // RNF Usabilidade: Mantém a interface limpa

        printf("===================================\n");
        printf("    MOCHILA DE LOOT (Nivel 1)      \n");
        printf("===================================\n");
        printf("Itens na mochila: %d / %d\n", totalItens, TAM_MOCHILA);
        printf("-----------------------------------\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("0. Sair do Jogo\n");
        printf("-----------------------------------\n");
        printf("Escolha uma opcao: ");
        
        // Leitura de dados 
        scanf("%d", &opcao);
        limparBuffer(); // Essencial para limpar o '\n' antes de usar fgets

        // RNF Manutenibilidade: 'switch' organiza o fluxo de execução
        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("\nSaindo do sistema de inventario...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
        }

        if (opcao != 0) {
            pausarSistema(); // RNF Usabilidade: Pausa para o usuário ler a saída
        }

    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções Obrigatórias ---

/**
 * @brief (Requisito: Cadastro de itens)
 * Adiciona um novo item ao final da lista sequencial (vetor 'mochila').
 * Verifica se a mochila está cheia antes de adicionar.
 */
void inserirItem() {
    limparTela();
    printf("--- 1. Adicionar Novo Item ---\n");

    // 1. Verifica se a mochila está cheia
    if (totalItens >= TAM_MOCHILA) {
        printf("[ERRO] Mochila cheia! Remova um item antes de adicionar outro.\n");
        return;
    }

    // 2. Se houver espaço, solicita os dados do novo item
    struct Item novoItem;

    printf("Nome do item (ex: Pistola, Municao 9mm): ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0; // Remove o '\n' do fgets

    printf("Tipo do item (ex: Arma, Municao, Cura): ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0; // Remove o '\n'

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBuffer(); // Limpa o buffer após o scanf

    // 3. Adiciona o item na próxima posição livre e incrementa o contador
    mochila[totalItens] = novoItem;
    totalItens++;

    printf("\n[SUCESSO] Item '%s' adicionado a mochila!\n", novoItem.nome);

    // Requisito: Listar após a operação (para o usuário ver o resultado)
    listarItens();
}

/**
 * @brief (Requisito: Listagem dos itens)
 * Percorre o vetor 'mochila' do início até 'totalItens'
 * e exibe os dados de cada item.
 */
void listarItens() {
    // Se a função foi chamada pelo menu, limpa a tela.
    // Se foi chamada por outra função (inserir/remover), 
    // a tela já estará limpa (não precisa limpar de novo).
    // Para simplificar, vamos padronizar a saída sem limpar a tela aqui.
    
    printf("\n--- 3. Itens na Mochila (%d/%d) ---\n", totalItens, TAM_MOCHILA);

    // 1. Verifica se a mochila está vazia
    if (totalItens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    // 2. Itera e exibe todos os itens (Uso de laços - Instrução)
    for (int i = 0; i < totalItens; i++) {
        printf("----------------------------------\n");
        printf(" Slot %d:\n", i + 1);
        printf("   Nome: %s\n", mochila[i].nome);
        printf("   Tipo: %s\n", mochila[i].tipo);
        printf("   Qtd:  %d\n", mochila[i].quantidade);
    }
    printf("----------------------------------\n");
}

/**
 * @brief (Requisito: Busca sequencial)
 * Pede um nome ao usuário e varre o vetor 'mochila'
 * comparando nomes. Para ao encontrar o primeiro resultado.
 */
void buscarItem() {
    limparTela();
    printf("--- 4. Buscar Item na Mochila ---\n");

    if (totalItens == 0) {
        printf("A mochila esta vazia. Nao ha o que buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remove o '\n'

    int encontrado = 0; // Flag para RNF de Usabilidade

    // 1. Implementação da busca sequencial 
    for (int i = 0; i < totalItens; i++) {
        // Compara o nome buscado com o nome do item atual (string.h)
        if (strcmp(nomeBusca, mochila[i].nome) == 0) {
            printf("\n[SUCESSO] Item encontrado!\n");
            printf("----------------------------------\n");
            printf("   Nome: %s\n", mochila[i].nome);
            printf("   Tipo: %s\n", mochila[i].tipo);
            printf("   Qtd:  %d\n", mochila[i].quantidade);
            printf("----------------------------------\n");
            
            encontrado = 1;
            break; // Para a busca após encontrar o primeiro item
        }
    }

    // 2. Mensagem de Usabilidade
    if (!encontrado) {
        printf("\n[ERRO] Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}

/**
 * @brief (Requisito: Remoção de itens)
 * Localiza um item pelo nome e o remove.
 * Para remover de um vetor, os itens subsequentes são "puxados"
 * uma posição para a esquerda.
 */
void removerItem() {
    limparTela();
    printf("--- 2. Remover Item da Mochila ---\n");

    if (totalItens == 0) {
        printf("A mochila esta vazia. Nao ha o que remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = 0; // Remove o '\n'

    int indexParaRemover = -1; // -1 significa "não encontrado"

    // 1. Buscar o índice do item 
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(nomeRemover, mochila[i].nome) == 0) {
            indexParaRemover = i;
            break; // Encontrou, pode parar de procurar
        }
    }

    // 2. Verificar se foi encontrado
    if (indexParaRemover == -1) {
        printf("\n[ERRO] Item '%s' nao encontrado na mochila.\n", nomeRemover);
        return;
    }

    // 3. Remover o item (sobrescrevendo com os itens seguintes)
    // Este laço "puxa" todos os elementos da frente para trás
    // (Uso de laços)
    for (int i = indexParaRemover; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    // 4. Decrementar o contador total de itens
    totalItens--;

    printf("\n[SUCESSO] Item '%s' removido da mochila.\n", nomeRemover);

    // Requisito: Listar após a operação
    listarItens();
}


// --- Funções Auxiliares (RNF: Usabilidade) ---

/**
 * @brief Limpa o buffer de entrada (stdin).
 * Essencial após usar scanf() para ler números, antes de usar fgets()
 * para ler strings, para consumir o caractere '\n' (Enter) restante.
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Limpa a tela do console.
 * Utiliza diretivas de pré-processamento para funcionar
 * tanto no Windows ("cls") quanto em sistemas baseados
 * em Unix ("clear").
 */
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * @brief Pausa a execução e aguarda o usuário pressionar Enter.
 * Melhora a usabilidade, permitindo que o usuário leia a 
 * saída de uma operação antes de retornar ao menu principal.
 */
void pausarSistema() {
    printf("\nPressione Enter para continuar...");
    limparBuffer(); // Aguarda o Enter
}