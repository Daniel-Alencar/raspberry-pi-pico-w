#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include "leds.h"
#include "buzzer.h"
#include "keyboard.h"

#define frequency 1000
#define duty_cycle 0.5

// Define os pinos do teclado com as portas GPIO
uint rows[] = {17, 18, 19, 20};
uint columns[] = {4, 8, 9, 16};

// Mapa de teclas como matriz 4x4
char KEY_MAP[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

int main() {
    stdio_init_all();

    init_leds_RGB();
    setup_buzzer(BUZZER_PIN, frequency);
    setup_keyboard(columns, rows);

    while (true) {

        char key = get_pressioned_key(KEY_MAP, rows, columns);
        if(key != 'F') {
            printf("Tecla pressionada: %c\n", key);

            switch (key) {
            case '1':
                printf("Liga led vermelho\n");
                turn_on_led(LED_RED);
                break;
            case '2':
                printf("Desliga led vermelho\n");
                turn_off_led(LED_RED);
                break;
            case '3':
                printf("Liga led verde\n");
                turn_on_led(LED_GREEN);
                break;
            case '4':
                printf("Desliga led verde\n");
                turn_off_led(LED_GREEN);
                break;
            case '5':
                printf("Liga led azul\n");
                turn_on_led(LED_BLUE);
                break;
            case '6':
                printf("Desliga led azul\n");
                turn_off_led(LED_BLUE);
                break;
            case '7':
                printf("Liga buzzer\n");
                play_buzzer(BUZZER_PIN, frequency, duty_cycle);
                break;
            case '8':
                printf("Desliga buzzer\n");
                stop_buzzer(BUZZER_PIN);
                break;
            default:
                break;
            }
        }
        sleep_ms(100);
    }
}
