#include <stdio.h>

// Inclui a biblioteca padrão para funcionalidades básicas como GPIO, temporização e comunicação serial.
#include "pico/stdlib.h"
// Inclui a biblioteca para gerenciamento de temporizadores de hardware.
#include "hardware/timer.h"

#include "traffic_light/traffic_light.h"

#define BUTTON_PIN 5

void setup_button() {
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
}

bool switching_leds_task_initialized = false;
uint traffic_light_state = 0;

int64_t switch_leds(alarm_id_t id, void *user_data) {

    traffic_light_state++;

    if(switching_leds_task_initialized) {
        if(traffic_light_state == 0) {
            printf("Três leds!\n");
            set_three_leds();
            add_alarm_in_ms(3000, switch_leds, NULL, false);
        } else if(traffic_light_state == 1) {
            printf("Dois leds!\n");
            set_two_leds();
            add_alarm_in_ms(3000, switch_leds, NULL, false);
        } else if(traffic_light_state == 2) {
            printf("Um led!\n");
            set_one_led();
            add_alarm_in_ms(3000, switch_leds, NULL, false);
        } else if(traffic_light_state == 3) {
            printf("Zero leds!\n");
            set_zero_led();
            switching_leds_task_initialized = false;
            traffic_light_state = 0;
        }
    }

    return 0;
}

int main()
{
    stdio_init_all();
    setup_traffic_light();
    setup_button();

    while (true) {
        // Verifica se o botão foi pressionado (nível baixo no pino) e se não foi inicializado.
        if (gpio_get(BUTTON_PIN) == 0 && !switching_leds_task_initialized) {
            // Adiciona um pequeno atraso para debounce, evitando leituras errôneas.
            sleep_ms(100);

            // Verifica novamente o estado do botão após o debounce.
            if (gpio_get(BUTTON_PIN) == 0) {
                switching_leds_task_initialized = true;

                printf("Clicou no botão!\n");
                printf("Três leds!\n");
                set_three_leds();

                add_alarm_in_ms(3000, switch_leds, NULL, false);
            }
        }
        sleep_ms(10);
    }
}
