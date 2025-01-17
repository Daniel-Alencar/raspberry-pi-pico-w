#include <stdio.h>
#include "pico/stdlib.h"

#define LED_PIN 12

void writeSymbol1() {
    gpio_put(LED_PIN, true);
    sleep_ms(200);
}

void writeSymbol2() {
    gpio_put(LED_PIN, true);
    sleep_ms(800);
}

void interval(int interval) {
    gpio_put(LED_PIN, false);
    sleep_ms(interval);
}

int main()
{
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    printf("Piscando o LED em código morse com a mensagem SOS...\r\n");

    while (true) {

        writeSymbol1();
        interval(125);
        writeSymbol1();
        interval(125);
        writeSymbol1();
        printf("S");

        interval(250);

        writeSymbol2();
        interval(125);
        writeSymbol2();
        interval(125);
        writeSymbol2();
        printf("O");

        interval(250);

        writeSymbol1();
        interval(125);
        writeSymbol1();
        interval(125);
        writeSymbol1();
        printf("S");

        interval(3000);
        printf("\r\n");
    }
}
