#include "simulador_esteira.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdlib.h>
#include <stdio.h>
#include "ssd1306.h" 
#include "simulador_falha.h"

// Variáveis globais de simulação da esteira
volatile int velocidade = 50;
volatile int contagem = 0;
volatile bool falha = false;        // Definida apenas aqui
volatile bool manutencao = false;
volatile int numero_blocos = 1; // Quantidade de blocos da esteira

// Retorna o estado atual de manutenção
bool esta_manutencao(void) {
    return manutencao;
}

void simular_esteira() {
    // Inicializa o I2C no i2c1 com 400 kHz
    i2c_init(i2c1, 400000);
    gpio_set_function(14, GPIO_FUNC_I2C);
    gpio_set_function(15, GPIO_FUNC_I2C);
    gpio_pull_up(14);
    gpio_pull_up(15);

    // Cria e inicializa a instância do display (SSD1306)
    tela_t tela;
    inicializar_tela(&tela, LARGURA, ALTURA, false, 0x3C, i2c1);
    configurar_tela(&tela);

    int pos_x_abs = 0;               // Posição absoluta acumulada da esteira
    const int update_interval = 100; // Tempo entre atualizações (ms)
    char buffer[32];

    // Parâmetros dos blocos
    const int block_width = 8;
    const int block_height = 8;
    const int espaco_entre_blocos = 4;
    int total_trajeto = LARGURA - block_width;  // Distância para completar um ciclo

    // Armazena o ciclo anterior para cada bloco (supondo no máximo 10 blocos)
    int prev_ciclo[10] = {0};

    while (true) {
        // Calcula o deslocamento com base na velocidade
        int delta = (int)(((float)velocidade / 50.0f) * 3.0f + 0.5f);

        // Se a esteira NÃO estiver em manutenção e não estiver em modo de falha, atualiza a posição
        if (!esta_manutencao() && !falha) {
            pos_x_abs += delta;
        }

        // Para desenho, calcula a posição base (módulo do trajeto)
        int pos_x = pos_x_abs % total_trajeto;

        // Atualiza a contagem para cada bloco
        for (int i = 0; i < numero_blocos; i++) {
            int bloco_abs = pos_x_abs + i * (block_width + espaco_entre_blocos);
            int ciclo = bloco_abs / total_trajeto;
            if (ciclo > prev_ciclo[i]) {
                contagem += (ciclo - prev_ciclo[i]);
                prev_ciclo[i] = ciclo;
            }
        }

        // Limpa o display
        preencher_tela(&tela, false);

        // Exibe informações no topo:
        sprintf(buffer, "Vel:%d%%", velocidade);
        desenhar_texto(&tela, buffer, 0, 0);
        sprintf(buffer, "Itens:%d", numero_blocos);
        desenhar_texto(&tela, buffer, 70, 0);
        sprintf(buffer, "Total:%d", contagem);
        desenhar_texto(&tela, buffer, 0, 10);

        // Exibe status na parte inferior centralizada:
        if (esta_manutencao() && !falha) {
            desenhar_texto(&tela, "MANUTENCAO", 30, 54);
        }
        else if (falha) {
            desenhar_texto(&tela, "FALHA", 44, 54);
        }
        
        // Desenha as bordas da esteira
        desenhar_linha_horizontal(&tela, 0, LARGURA - 1, 30, true);
        desenhar_linha_horizontal(&tela, 0, LARGURA - 1, 50, true);

        // Desenha os blocos da esteira
        int item_y = 34;
        for (int i = 0; i < numero_blocos; i++) {
            int pos_x_item = pos_x + i * (block_width + espaco_entre_blocos);
            if (pos_x_item > (LARGURA - block_width)) {
                pos_x_item = pos_x_item % (LARGURA - block_width);
            }
            for (int dx = 0; dx < block_width; dx++) {
                for (int dy = 0; dy < block_height; dy++) {
                    desenhar_pixel(&tela, pos_x_item + dx, item_y + dy, true);
                }
            }
        }

        enviar_dados_tela(&tela);
        sleep_ms(update_interval);
    }
}
