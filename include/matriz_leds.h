#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>
#include "pico/stdlib.h"

// Número total de LEDs na matriz (5x5)
#define NUM_LEDS_MTX 25

// Nível de brilho padrão para os LEDs da matriz
#define NIVEL_LED_MTX 255

// Estrutura para representar um LED RGB
typedef struct {
    uint8_t R;
    uint8_t G;
    uint8_t B;
} led_t;

// Declara o buffer da matriz de LEDs
extern led_t matriz_leds[NUM_LEDS_MTX];

// Protótipos das funções para manipular a matriz de LEDs
void inicializar_matriz_leds(uint pino);
void definir_led(uint id, uint8_t R, uint8_t G, uint8_t B);
void limpar_leds(void);
uint32_t valor_rgb(uint8_t B, uint8_t R, uint8_t G);
void escrever_leds(void);
void definir_led_por_padrao(const uint8_t padrao[5][5]);

#endif // LEDS_H
