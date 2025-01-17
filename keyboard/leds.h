#include <pico/stdlib.h>

#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12

void init_leds_RGB() {
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
}

void run_leds() {
    gpio_put(LED_RED, true);
    sleep_ms(500);
    gpio_put(LED_RED, false);
    sleep_ms(500);

    gpio_put(LED_GREEN, true);
    sleep_ms(500);
    gpio_put(LED_GREEN, false);
    sleep_ms(500);

    gpio_put(LED_BLUE, true);
    sleep_ms(500);
    gpio_put(LED_BLUE, false);
    sleep_ms(500);
}

void turn_on_led(uint LED) {
  gpio_put(LED, true);
}

void turn_off_led(uint LED) {
  gpio_put(LED, false);
}