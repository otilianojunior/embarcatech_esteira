#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "simulador_esteira.h"
#include "alterar_itens.h"
#include "simulador_falha.h"
#include "joystick_controle.h"
#include "matriz_leds.h"
#include <stdio.h>

int main() {
    stdio_init_all();
    sleep_ms(10000);
    printf("Iniciando o sistema de monitoramento da esteira\n");

    // Inicializa os botões de alterar itens (botão A)
    iniciar_alterar_itens();
    
    // Inicializa o joystick (ADC para eixo Y e botão para pausar/resumir)
    iniciar_joystick_controle();

    // Inicializa o simulador de falha (botão B e buzzers)
    inicializar_simulador_falha();

    // Inicializa a matriz de LEDs (ex: pino 7)
    inicializar_matriz_leds(7);

    // Lança a simulação da esteira na core 1 (que atualiza o display)
    multicore_launch_core1(simular_esteira);

    // Loop principal: mantém o Wi‑Fi ativo, atualiza a velocidade via joystick,
    // processa o botão do joystick e verifica/executa o alarme de falha.
    while (true) {
        // Atualiza a velocidade da esteira usando o joystick
        atualizar_velocidade_joystick();

        // Processa o botão do joystick se pressionado
        if (gpio_get(BOTAO_JOYSTICK) == 0) {
            processar_botao_joystick();
            sleep_ms(300);
        }

        // Verifica se há falha no sistema
        verificar_falha();

        // Executa o alarme de falha se uma falha for detectada
        if (falha) {
            executar_alarme_falha();
        }

        sleep_ms(100);
    }
    
    return 0;
}