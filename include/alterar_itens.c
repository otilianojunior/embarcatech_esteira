#include "alterar_itens.h"  // ou renomeie para alterar_itens.h se preferir
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "simulador_esteira.h"  // Para acessar a variável 'numero_blocos'
#include <stdio.h>

#define BOTAO_A_GPIO 5
#define DEBOUNCE_DELAY_MS 200

#define NUMERO_BLOCOS_MIN 1
#define NUMERO_BLOCOS_MAX 5

// Variável estática para controlar a direção: 1 = aumentando, -1 = diminuindo.
static int direcao = 1;
static absolute_time_t ultimo_tempo_botao_a = {0};

void callback_botao_a(uint32_t gpio, uint32_t events) {
    absolute_time_t agora = get_absolute_time();
    if (absolute_time_diff_us(ultimo_tempo_botao_a, agora) < DEBOUNCE_DELAY_MS * 1000)
        return;
    ultimo_tempo_botao_a = agora;

    if (direcao == 1) { // modo aumentar
        if (numero_blocos < NUMERO_BLOCOS_MAX) {
            numero_blocos++;
            if (numero_blocos == NUMERO_BLOCOS_MAX) {
                // Muda para modo diminuir após atingir o máximo
                direcao = -1;
            }
        }
    } else { // modo diminuir
        if (numero_blocos > NUMERO_BLOCOS_MIN) {
            numero_blocos--;
            if (numero_blocos == NUMERO_BLOCOS_MIN) {
                // Muda para modo aumentar após atingir o mínimo
                direcao = 1;
            }
        }
    }
    printf("Botão A pressionado. Número de blocos: %d\n", numero_blocos);
}

void iniciar_alterar_itens(void) {
    gpio_init(BOTAO_A_GPIO);
    gpio_set_dir(BOTAO_A_GPIO, GPIO_IN);
    gpio_pull_up(BOTAO_A_GPIO);
    // Registra o callback para a interrupção do botão A
    gpio_set_irq_enabled_with_callback(BOTAO_A_GPIO, GPIO_IRQ_EDGE_FALL, true, (gpio_irq_callback_t) callback_botao_a);

}
