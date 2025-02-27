#ifndef JOYSTICK_CONTROLE_H
#define JOYSTICK_CONTROLE_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Define o pino do botão do joystick
#define BOTAO_JOYSTICK 22

// Inicializa o ADC para o joystick (e configura o botão do joystick para manutenção/retomada)
// Esta função deve ser chamada uma vez durante a inicialização do sistema
void iniciar_joystick_controle(void);

// Atualiza a velocidade da esteira com base no valor do eixo Y do joystick
// Esta função deve ser chamada periodicamente para ajustar a velocidade
void atualizar_velocidade_joystick(void);

// Processa o botão do joystick (BOTAO_JOYSTICK) para alternar o estado de manutenção
// Esta função deve ser chamada quando o botão do joystick for pressionado
void processar_botao_joystick(void);

// Retorna true se a esteira estiver em manutenção, false caso contrário
bool esta_manutencao(void);

#ifdef __cplusplus
}
#endif

#endif // JOYSTICK_CONTROLE_H
