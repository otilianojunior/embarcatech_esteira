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

// Inicializa o PIO e a matriz de LEDs
// Parâmetros:
// - pino: número do pino GPIO ao qual a matriz de LEDs está conectada
void inicializar_matriz_leds(uint pino);

// Define a cor de um LED específico na matriz
// Parâmetros:
// - id: índice do LED na matriz
// - R: valor do componente vermelho (0-255)
// - G: valor do componente verde (0-255)
// - B: valor do componente azul (0-255)
void definir_led(uint id, uint8_t R, uint8_t G, uint8_t B);

// Limpa todos os LEDs da matriz (desliga todos)
void limpar_leds(void);

// Converte os valores RGB para um único uint32_t
// Parâmetros:
// - B: valor do componente azul (0-255)
// - R: valor do componente vermelho (0-255)
// - G: valor do componente verde (0-255)
// Retorna: valor RGB combinado em um uint32_t
uint32_t valor_rgb(uint8_t B, uint8_t R, uint8_t G);

// Escreve os valores dos LEDs na matriz
void escrever_leds(void);

// Define os LEDs da matriz com base em um padrão 5x5
// Parâmetros:
// - padrao: matriz 5x5 de valores (0 ou 1) indicando quais LEDs acender
void definir_led_por_padrao(const uint8_t padrao[5][5]);

#endif // LEDS_H
