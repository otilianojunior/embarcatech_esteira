#include "joystick_controle.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "simulador_esteira.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Utiliza o pino 26 para o eixo Y
#define PINO_Y_JOYSTICK 26

// Calibração para um ADC de 12 bits (0 a 4095)
#define JOY_Y_CENTRO 2048
#define ZONA_MORTA 60

// Parâmetros para ajuste de velocidade
#define AJUSTE_MAX 10
#define VELOCIDADE_MIN 10
#define VELOCIDADE_MAX 100

static absolute_time_t ultimo_tempo_adc = {0};
static absolute_time_t ultimo_tempo_botao = {0};

// Inicializa o joystick e o botão associado
void iniciar_joystick_controle(void) {
    adc_init();
    adc_gpio_init(PINO_Y_JOYSTICK);
    
    gpio_init(BOTAO_JOYSTICK);
    gpio_set_dir(BOTAO_JOYSTICK, GPIO_IN);
    gpio_pull_up(BOTAO_JOYSTICK);
}

// Atualiza a velocidade da esteira com base na posição do joystick
void atualizar_velocidade_joystick(void) {
    // Não altera a velocidade se a esteira estiver em manutenção
    if (manutencao) return;

    adc_select_input(0);
    uint16_t valor = adc_read();

    int diferenca = (int)valor - JOY_Y_CENTRO;
    if (abs(diferenca) < ZONA_MORTA) {
        return;
    }

    int ajuste = (diferenca * AJUSTE_MAX) / JOY_Y_CENTRO;
    int nova_velocidade = velocidade + ajuste;
    if (nova_velocidade < VELOCIDADE_MIN) nova_velocidade = VELOCIDADE_MIN;
    if (nova_velocidade > VELOCIDADE_MAX) nova_velocidade = VELOCIDADE_MAX;

    if (nova_velocidade != velocidade) {
        velocidade = nova_velocidade;
        printf("Joystick ajustou velocidade para %d%%\n", velocidade);
    }
}

// Processa o botão do joystick para alternar o estado de manutenção
void processar_botao_joystick(void) {
    absolute_time_t agora = get_absolute_time();
    if (absolute_time_diff_us(ultimo_tempo_botao, agora) < 200 * 1000)
        return;
    ultimo_tempo_botao = agora;
    
    // Alterna o estado de manutenção (usa a variável global "manutencao")
    manutencao = !manutencao;
    if (manutencao) {
        printf("Joystick: Esteira em manutenção\n");
    } else {
        printf("Joystick: Esteira retomada\n");
    }
}