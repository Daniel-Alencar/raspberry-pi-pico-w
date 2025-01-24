#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

// Arquivo .pio
#include "pio_matrix.pio.h"

// Pino de saída
#define OUT_PIN 7

#define COLUMNS 5
#define ROWS 5
#define NUM_LEDS 25
#define LAYERS 3

PIO pio;
uint offset, sm;

void setup_led_matrix() {
    pio = pio0; 
    bool ok;
    
    // Coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
    ok = set_sys_clock_khz(128000, false);

    // Inicializa todos os códigos stdio padrão que estão ligados ao binário.
    stdio_init_all();

    printf("iniciando a transmissão PIO");
    if (ok) printf("clock set to %ld\n", clock_get_hz(clk_sys));

    // Configurações da PIO
    offset = pio_add_program(pio, &pio_matrix_program);
    sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);
}

void bin_printf(int num) {
 int i;
 for (i = 31; i >= 0; i--) {
  (num & (1 << i)) ? printf("1") : printf("0");
 }
}

uint32_t matrix_rgb(double b, double r, double g)
{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

double convertDrawingToMatrixIndex(
    double* desenho, int index
) {
    int actualRow = index / COLUMNS;
    int actualColumn = index % COLUMNS;
    if(actualRow % 2) {
        return desenho[(actualRow * COLUMNS) + (COLUMNS - 1 - actualColumn)];
    } else {
        return desenho[index];
    }
}

void draw(
    double **desenhoRGB
){
    uint32_t led_value;
    for (int16_t i = 0; i < NUM_LEDS; i++) {
        led_value = matrix_rgb(
            convertDrawingToMatrixIndex(
              desenhoRGB[0], NUM_LEDS - 1 - i
            ),
            convertDrawingToMatrixIndex(
              desenhoRGB[1], NUM_LEDS - 1 - i
            ),
            convertDrawingToMatrixIndex(
              desenhoRGB[2], NUM_LEDS - 1 - i
            )
        );
        pio_sm_put_blocking(pio, sm, led_value);
    }
    bin_printf(led_value);
}

void animate(
  double*** movie,
  uint frames,
  uint sleep_time
) {
  for(int i = 0; i < frames; i++) {
    draw(movie[i]);
    sleep_ms(sleep_time);
  }
}