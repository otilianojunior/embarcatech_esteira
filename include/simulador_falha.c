#include "simulador_falha.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "matriz_leds.h"

// Definições dos pinos
#define BOTAO_B      6
#define BUZZER_A     21
#define BUZZER_B     10

// Parâmetros do tom e do alarme
#define FREQUENCIA_TOM       262   // Frequência aproximada para "dó" (Hz)
#define DURACAO_NOTA_MS       100   // Duração de cada nota (ms)
#define PAUSA_ENTRE_NOTAS_MS  100   // Pausa entre toques (ms)
#define DURACAO_LED_MS        100   // Duração do piscar do LED (ms)
#define PAUSA_ENTRE_CICLOS_MS 300   // Pausa extra entre ciclos

// Intensidade do LED: 10% de 255
#define INTENSIDADE_LED 25

// Note que não definimos a variável "falha" aqui, pois ela já é definida em simulador_esteira.c

// Inicializa o simulador de falha
void inicializar_simulador_falha(void) {
    // Configura o botão B (entrada com pull-up)
    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_B);

    // Configura os buzzers (saídas)
    gpio_init(BUZZER_A);
    gpio_set_dir(BUZZER_A, GPIO_OUT);
    gpio_init(BUZZER_B);
    gpio_set_dir(BUZZER_B, GPIO_OUT);
    
    // Inicializa a matriz de LEDs
    limpar_leds();
    escrever_leds();
}

// Toca um tom nos buzzers
void tocar_tom(uint frequencia, uint duracao_ms) {
    uint periodo_us = 1000000 / frequencia;
    uint meio_periodo_us = periodo_us / 2;
    uint iteracoes = (duracao_ms * 1000) / periodo_us;
    for (uint i = 0; i < iteracoes; i++) {
        gpio_put(BUZZER_A, 1);
        gpio_put(BUZZER_B, 1);
        sleep_us(meio_periodo_us);
        gpio_put(BUZZER_A, 0);
        gpio_put(BUZZER_B, 0);
        sleep_us(meio_periodo_us);
        verificar_falha();
        if (!falha) break;
    }
}

// Pisca a matriz de LEDs na cor vermelha
void piscar_matriz_vermelha(uint duracao_ms) {
    // Define todos os LEDs da matriz para vermelho com 10% de intensidade
    for (uint i = 0; i < NUM_LEDS_MTX; i++) {
         definir_led(i, 25, 0, 0);
    }
    escrever_leds();
    // Função auxiliar para aguardar em pequenos passos
    const uint passo = 10;
    uint decorrido = 0;
    while (decorrido < duracao_ms && falha) {
        sleep_ms(passo);
        decorrido += passo;
        verificar_falha();
    }
    limpar_leds();
    escrever_leds();
}

// Executa o alarme de falha
void executar_alarme_falha(void) {
    for (int i = 0; i < 3; i++) {
        if (!falha) break;
        tocar_tom(FREQUENCIA_TOM, DURACAO_NOTA_MS);
        if (!falha) break;
        piscar_matriz_vermelha(DURACAO_LED_MS);
        if (!falha) break;
        // Pequena pausa entre notas
        sleep_ms(PAUSA_ENTRE_NOTAS_MS);
    }
    sleep_ms(PAUSA_ENTRE_CICLOS_MS);
}

// Verifica o estado do botão de falha
void verificar_falha(void) {
    if (gpio_get(BOTAO_B) == 0) {
        sleep_ms(50);  // Debounce
        if (gpio_get(BOTAO_B) == 0) {
            falha = !falha;  // Inverte o estado
            while (gpio_get(BOTAO_B) == 0) {
                sleep_ms(10);
            }
        }
    }
}
