#ifndef SIMULADOR_FALHA_H
#define SIMULADOR_FALHA_H

#include "pico/stdlib.h"

void inicializar_simulador_falha(void);
void tocar_tom(uint frequencia, uint duracao_ms);
void piscar_matriz_vermelha(uint duracao_ms);
void executar_alarme_falha(void);
void verificar_falha(void);

extern volatile bool falha;  // Unifica com o definido em simulador_esteira.c

#endif // SIMULADOR_FALHA_H
