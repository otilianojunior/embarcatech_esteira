#ifndef ALTERAR_ITENS_H
#define ALTERAR_ITENS_H

#include <stdint.h>  // Para uint32_t

#ifdef __cplusplus
extern "C" {
#endif

// Inicializa o botão A (GPIO 5) para alternar a quantidade de itens na esteira
void iniciar_alterar_itens(void);

// Handler para o botão A; deve ser chamado pelo callback global
void callback_botao_a(uint32_t gpio, uint32_t events);

#ifdef __cplusplus
}
#endif

#endif // ALTERAR_ITENS_H
