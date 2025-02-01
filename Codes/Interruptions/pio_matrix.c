#include <stdio.h>
#include "pico/stdlib.h"

#include "led_matrix/led_matrix.h"
#include "buttons/buttons.h"
#include "led_rgb/led_rgb.h"

// Indice do desenho
int index_numbers = 0;

// Armazena o tempo do último evento (em microssegundos)
static volatile uint32_t last_time = 0;

// Função de interrupção para funcionamento dos botões
static void gpio_irq_handler(uint gpio, uint32_t events);

int main()
{
    // Configurações iniciais
    stdio_init_all();
    setup_buttons();
    setup_led_RGB();
    setup_led_matrix();
    setup_intensity_leds(0, 255, 0);

    // Interrupções configuradas
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    // Desenha o primeiro número (0)
    draw(numbers[index_numbers]);

    while (true) {
        // Pisca o led vermelho em 5 FPS
        gpio_put(LED_RED, true);
        sleep_ms(100);
        gpio_put(LED_RED, false);
        sleep_ms(100);
    }
}

void gpio_irq_handler(uint gpio, uint32_t events) {
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    // Verifica se passou tempo suficiente desde o último evento
    // 200 ms de debouncing
    if (current_time - last_time > 200000) 
    {   
        // Atualiza o tempo do último evento
        last_time = current_time;

        // Faz as funcionalidades dos botões
        if(gpio == BUTTON_A) {
            index_numbers = ++index_numbers % 10;
            printf("Incremento do índice: %d\n", index_numbers);
            draw(numbers[index_numbers]);
        } else if(gpio == BUTTON_B) {
            index_numbers = --index_numbers < 0 ? 9 : index_numbers;
            printf("Decremento do índice: %d\n", index_numbers);
            draw(numbers[index_numbers]);
        }
    }
}