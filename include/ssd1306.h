#ifndef SSD1306_H
#define SSD1306_H 

#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Dimensões do display
#define LARGURA 128
#define ALTURA 64

// Comandos do display SSD1306 (valores fixos)
typedef enum {
   SET_CONTRAST = 0x81,
   SET_ENTIRE_ON = 0xA4,
   SET_NORM_INV = 0xA6,
   SET_DISP = 0xAE,
   SET_MEM_ADDR = 0x20,
   SET_COL_ADDR = 0x21,
   SET_PAGE_ADDR = 0x22,
   SET_DISP_START_LINE = 0x40,
   SET_SEG_REMAP = 0xA0,
   SET_MUX_RATIO = 0xA8,
   SET_COM_OUT_DIR = 0xC0,
   SET_DISP_OFFSET = 0xD3,
   SET_COM_PIN_CFG = 0xDA,
   SET_DISP_CLK_DIV = 0xD5,
   SET_PRECHARGE = 0xD9,
   SET_VCOM_DESEL = 0xDB,
   SET_CHARGE_PUMP = 0x8D
} ssd1306_command_t;

// Estrutura do display
typedef struct {
   uint8_t largura, altura, paginas, endereco;
   i2c_inst_t *porta_i2c;
   bool vcc_externo;
   uint8_t *buffer_ram;
   size_t tam_buffer;
   uint8_t buffer_porta[2];
} tela_t;

// Inicializa o display
// Parâmetros:
// - tela: ponteiro para a estrutura do display
// - largura: largura do display em pixels
// - altura: altura do display em pixels
// - vcc_externo: true se o display usa VCC externo, false caso contrário
// - endereco: endereço I2C do display
// - porta_i2c: instância da porta I2C
void inicializar_tela(tela_t *tela, uint8_t largura, uint8_t altura, bool vcc_externo, uint8_t endereco, i2c_inst_t *porta_i2c);

// Configura o display com os comandos necessários
// Parâmetros:
// - tela: ponteiro para a estrutura do display
void configurar_tela(tela_t *tela);

// Envia um comando ao display
// Parâmetros:
// - tela: ponteiro para a estrutura do display
// - comando: comando a ser enviado
void enviar_comando_tela(tela_t *tela, uint8_t comando);

// Envia os dados do buffer para o display
// Parâmetros:
// - tela: ponteiro para a estrutura do display
void enviar_dados_tela(tela_t *tela);

// Desenha um pixel no display
// Parâmetros:
// - tela: ponteiro para a estrutura do display
// - x: coordenada x do pixel
// - y: coordenada y do pixel
// - valor: true para acender o pixel, false para apagar
void desenhar_pixel(tela_t *tela, uint8_t x, uint8_t y, bool valor);

// Preenche todo o display com um valor
// Parâmetros:
// - tela: ponteiro para a estrutura do display
// - valor: true para acender todos os pixels, false para apagar
void preencher_tela(tela_t *tela, bool valor);

// Desenha um retângulo (opcionalmente preenchido)
// Parâmetros:
// - tela: ponteiro para a estrutura do display
// - topo: coordenada y do topo do retângulo
// - esquerda: coordenada x da esquerda do retângulo
// - largura: largura do retângulo
// - altura: altura do retângulo
// - valor: true para acender os pixels, false para apagar
// - preenche: true para preencher o retângulo, false para desenhar apenas as bordas
void desenhar_retangulo(tela_t *tela, uint8_t topo, uint8_t esquerda, uint8_t largura, uint8_t altura, bool valor, bool preencher);

// Desenha uma linha usando o algoritmo de Bresenham
// Parâmetros:
// - tela: ponteiro para a estrutura do display
// - x0: coordenada x do ponto inicial
// - y0: coordenada y do ponto inicial
// - x1: coordenada x do ponto final
// - y1: coordenada y do ponto final
// - valor: true para acender os pixels, false para apagar
void desenhar_linha(tela_t *tela, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool valor);

// Desenha uma linha horizontal
// Parâmetros:
// - tela: ponteiro para a estrutura do display
// - x0: coordenada x inicial
// - x1: coordenada x final
// - y: coordenada y da linha
// - valor: true para acender os pixels, false para apagar
void desenhar_linha_horizontal(tela_t *tela, uint8_t x0, uint8_t x1, uint8_t y, bool valor);

// Desenha uma linha vertical
// Parâmetros:
// - tela: ponteiro para a estrutura do display
// - x: coordenada x da linha
// - y0: coordenada y inicial
// - y1: coordenada y final
// - valor: true para acender os pixels, false para apagar
void desenhar_linha_vertical(tela_t *tela, uint8_t x, uint8_t y0, uint8_t y1, bool valor);

// Desenha um caractere (8x8) utilizando a fonte
// Parâmetros:
// - tela: ponteiro para a estrutura do display
// - c: caractere a ser desenhado
// - x: coordenada x do caractere
// - y: coordenada y do caractere
void desenhar_caractere(tela_t *tela, char c, uint8_t x, uint8_t y);

// Desenha uma string no display
// Parâmetros:
// - tela: ponteiro para a estrutura do display
// - texto: string a ser desenhada
// - x: coordenada x inicial
// - y: coordenada y inicial
void desenhar_texto(tela_t *tela, const char *texto, uint8_t x, uint8_t y);

#endif