
#define LED_RED 11
#define LED_YELLOW 12
#define LED_GREEN 13

#define LED_RED_BDL 13
#define LED_GREEN_BDL 11
#define LED_BLUE_BDL 12

#define USE_BITDOGLAB 1

void setup_traffic_light() {
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);

    gpio_init(LED_YELLOW);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
}

void set_red() {
    if(USE_BITDOGLAB) {
        gpio_put(LED_RED_BDL, true);
        gpio_put(LED_GREEN_BDL, false);
        gpio_put(LED_BLUE_BDL, false);
    } else {
        gpio_put(LED_RED, true);
        gpio_put(LED_YELLOW, false);
        gpio_put(LED_GREEN, false);
    }
}

void set_yellow() {
    if(USE_BITDOGLAB) {
        gpio_put(LED_RED_BDL, true);
        gpio_put(LED_GREEN_BDL, true);
        gpio_put(LED_BLUE_BDL, false);
    } else {
        gpio_put(LED_RED, false);
        gpio_put(LED_YELLOW, true);
        gpio_put(LED_GREEN, false);
    }
}

void set_green() {
    if(USE_BITDOGLAB) {
        gpio_put(LED_RED_BDL, false);
        gpio_put(LED_GREEN_BDL, true);
        gpio_put(LED_BLUE_BDL, false);
    } else {
        gpio_put(LED_RED, false);
        gpio_put(LED_YELLOW, false);
        gpio_put(LED_GREEN, true);
    }
}