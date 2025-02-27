#ifndef SIMULADOR_FALHA_H
#define SIMULADOR_FALHA_H

#include "pico/stdlib.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Inicializa o simulador de falha
void inicializar_simulador_falha(void);

// Toca um tom nos buzzers
// Parâmetros:
// - frequencia: frequência do tom em Hz
// - duracao_ms: duração do tom em milissegundos
void tocar_tom(uint frequencia, uint duracao_ms);

// Pisca a matriz de LEDs na cor vermelha
// Parâmetros:
// - duracao_ms: duração do piscar em milissegundos
void piscar_matriz_vermelha(uint duracao_ms);

// Executa o alarme de falha
void executar_alarme_falha(void);

// Verifica o estado do botão de falha
void verificar_falha(void);

extern volatile bool falha;  // Unifica com o definido em simulador_esteira.c

#ifdef __cplusplus
}
#endif

#endif // SIMULADOR_FALHA_H
