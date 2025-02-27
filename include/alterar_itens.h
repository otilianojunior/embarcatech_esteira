#ifndef ALTERAR_ITENS_H
#define ALTERAR_ITENS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Inicializa o botão A (GPIO 5) para alternar a quantidade de itens na esteira
// Esta função deve ser chamada uma vez durante a inicialização do sistema
void iniciar_alterar_itens(void);

// Handler para o botão A; deve ser chamado pelo callback global
// Esta função será chamada quando o botão A for pressionado
// Parâmetros:
// - gpio: número do GPIO que gerou o evento
// - events: tipo de evento ocorrido (ex: pressionado, solto)
void callback_botao_a(uint32_t gpio, uint32_t events);

#ifdef __cplusplus
}
#endif

#endif // ALTERAR_ITENS_H
