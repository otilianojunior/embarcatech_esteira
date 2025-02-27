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
bool esta_manutencao(void);
void simular_esteira(void);

#ifdef __cplusplus
}
#endif

#endif // SIMULADOR_ESTEIRA_H
