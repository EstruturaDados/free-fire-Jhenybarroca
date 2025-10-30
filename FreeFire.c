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

