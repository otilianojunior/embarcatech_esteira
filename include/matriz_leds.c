#include "matriz_leds.h"
#include <string.h>
#include "hardware/pio.h"
#include "ws2812.pio.h"

// Definição do buffer de LEDs
led_t matriz_leds[NUM_LEDS_MTX];

// Variáveis internas para o PIO e state machine
static PIO pio_inst;
static uint sm;

// Função para inicializar o PIO e a matriz de LEDs
void inicializar_matriz_leds(uint pino) {
    // Inicializa o PIO: por exemplo, utilizando o pio0 e reclamando um state machine
    pio_inst = pio0;  // ou pio1, se preferir
    sm = pio_claim_unused_sm(pio_inst, true);

    // Se você estiver usando um programa PIO (por exemplo, para ws2812), adicione:
    uint offset = pio_add_program(pio_inst, &ws2812_program);
    ws2812_program_init(pio_inst, sm, offset, pino, 800000, false);

    // Inicializa o buffer de LEDs apagado
    limpar_leds();
    escrever_leds();
}

// Define a cor de um LED específico na matriz
void definir_led(uint id, uint8_t R, uint8_t G, uint8_t B) {
    if(id < NUM_LEDS_MTX) {
        matriz_leds[id].R = R;
        matriz_leds[id].G = G;
        matriz_leds[id].B = B;
    }
}

// Limpa todos os LEDs da matriz (desliga todos)
void limpar_leds(void) {
    for (uint i = 0; i < NUM_LEDS_MTX; i++) {
        matriz_leds[i].R = 0;
        matriz_leds[i].G = 0;
        matriz_leds[i].B = 0;
    }
}

// Converte os valores RGB para um único uint32_t
uint32_t valor_rgb(uint8_t B, uint8_t R, uint8_t G) {
    return (G << 24) | (R << 16) | (B << 8);
}

// Escreve os valores dos LEDs na matriz
void escrever_leds(void) {
    uint32_t valor;
    for (uint i = 0; i < NUM_LEDS_MTX; ++i) {
        valor = valor_rgb(matriz_leds[i].B, matriz_leds[i].R, matriz_leds[i].G);
        pio_sm_put_blocking(pio_inst, sm, valor);
    }
}

// Define os LEDs da matriz com base em um padrão 5x5
void definir_led_por_padrao(const uint8_t padrao[5][5]) {
    uint8_t nivel = NIVEL_LED_MTX;
    int idx = 0;
    // Varre as linhas de baixo para cima com varredura em ziguezague
    for (int linha = 4; linha >= 0; linha--) {
        bool reverso = (linha % 2 == 0);
        if (reverso) {
            for (int coluna = 4; coluna >= 0; coluna--) {
                if (padrao[linha][coluna])
                    definir_led(idx, 0, 0, nivel);
                else
                    definir_led(idx, 0, 0, 0);
                idx++;
            }
        } else {
            for (int coluna = 0; coluna < 5; coluna++) {
                if (padrao[linha][coluna])
                    definir_led(idx, 0, 0, nivel);
                else
                    definir_led(idx, 0, 0, 0);
                idx++;
            }
        }
    }
}
