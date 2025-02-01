
#define LED_RED 11
#define LED_YELLOW 12
#define LED_GREEN 13

void setup_traffic_light() {
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);

    gpio_init(LED_YELLOW);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
}

void set_three_leds() {
    gpio_put(LED_RED, true);
    gpio_put(LED_YELLOW, true);
    gpio_put(LED_GREEN, true);
}

void set_two_leds() {
    gpio_put(LED_RED, false);
    gpio_put(LED_YELLOW, true);
    gpio_put(LED_GREEN, true);
}

void set_one_led() {
    gpio_put(LED_RED, false);
    gpio_put(LED_YELLOW, false);
    gpio_put(LED_GREEN, true);
}

void set_zero_led() {
    gpio_put(LED_RED, false);
    gpio_put(LED_YELLOW, false);
    gpio_put(LED_GREEN, false);
}