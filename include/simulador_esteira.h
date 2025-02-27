#ifndef SIMULADOR_ESTEIRA_H
#define SIMULADOR_ESTEIRA_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Variáveis globais
extern volatile int velocidade;
extern volatile int contagem;
extern volatile bool falha;
extern volatile bool manutencao;
extern volatile int numero_blocos;

// Protótipos de funções

// Retorna o estado atual de manutenção
// Retorna: true se a esteira estiver em manutenção, false caso contrário
bool esta_manutencao(void);

// Função principal para simular a esteira
void simular_esteira(void);

#ifdef __cplusplus
}
#endif

#endif // SIMULADOR_ESTEIRA_H
