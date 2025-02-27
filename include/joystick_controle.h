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
void iniciar_joystick_controle(void);

// Atualiza a velocidade da esteira com base no valor do eixo Y do joystick
void atualizar_velocidade_joystick(void);

// Processa o botão do joystick (BOTAO_JOYSTICK) para alternar o estado de manutenção
void processar_botao_joystick(void);

// Retorna true se a esteira estiver em manutenção, false caso contrário
bool esta_manutencao(void);

#ifdef __cplusplus
}
#endif

#endif // JOYSTICK_CONTROLE_H
