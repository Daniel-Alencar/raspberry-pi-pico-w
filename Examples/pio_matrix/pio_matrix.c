#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

//other libraries
#include "led_matrix.h"

//botão de interupção
const uint button_0 = 5;
const uint button_1 = 6;

double drawning_red_1[NUM_LEDS] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0
};

double drawning_green_1[NUM_LEDS] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.2, 0.0, 0.0, 0.0,
    0.2, 0.2, 0.2, 0.0, 0.0
};

double drawning_blue_1[NUM_LEDS] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0
};

double drawning_red_2[NUM_LEDS] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.2, 0.0, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0
};

double drawning_green_2[NUM_LEDS] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.2, 0.0, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0
};

double drawning_blue_2[NUM_LEDS] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.2, 0.0, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0
};

double drawning_red_3[NUM_LEDS] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.2, 0.0,
    0.0, 0.0, 0.2, 0.2, 0.2
};

double drawning_green_3[NUM_LEDS] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.2, 0.0,
    0.0, 0.0, 0.2, 0.2, 0.2
};

double drawning_blue_3[NUM_LEDS] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.2, 0.0,
    0.0, 0.0, 0.2, 0.2, 0.2
};

double drawning_red_4[NUM_LEDS] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.2, 0.0, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0
};

double drawning_green_4[NUM_LEDS] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.2, 0.0, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0
};

double drawning_blue_4[NUM_LEDS] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.2, 0.0, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0
};

double drawning_red_5[NUM_LEDS] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.2, 0.0, 0.0, 0.0,
    0.2, 0.2, 0.2, 0.0, 0.0
};

double drawning_green_5[NUM_LEDS] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.2, 0.0, 0.0, 0.0,
    0.2, 0.2, 0.2, 0.0, 0.0
};

double drawning_blue_5[NUM_LEDS] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.2, 0.0, 0.0, 0.0,
    0.2, 0.2, 0.2, 0.0, 0.0
};

double* frame1[LAYERS] = {
    drawning_blue_1,
    drawning_red_1,
    drawning_green_1,
};
double* frame2[LAYERS] = {
    drawning_blue_2,
    drawning_red_2,
    drawning_green_2,
};
double* frame3[LAYERS] = {
    drawning_blue_3,
    drawning_red_3,
    drawning_green_3,
};
double* frame4[LAYERS] = {
    drawning_blue_4,
    drawning_red_4,
    drawning_green_4,
};
double* frame5[LAYERS] = {
    drawning_blue_5,
    drawning_red_5,
    drawning_green_5,
};

double **movie[] = {
    frame1,
    frame2,
    frame3,
    frame4,
    frame5
};

//rotina da interrupção
static void gpio_irq_handler(uint gpio, uint32_t events){
    printf("Interrupção ocorreu no pino %d, no evento %d\n", gpio, events);
    printf("HABILITANDO O MODO GRAVAÇÃO");
    //habilita o modo de gravação do microcontrolador
	reset_usb_boot(0,0); 
}

//função principal
int main()
{   
    setup_led_matrix();
    
    //inicializar o botão de interrupção - GPIO5
    gpio_init(button_0);
    gpio_set_dir(button_0, GPIO_IN);
    gpio_pull_up(button_0);

    //inicializar o botão de interrupção - GPIO5
    gpio_init(button_1);
    gpio_set_dir(button_1, GPIO_IN);
    gpio_pull_up(button_1);

    //interrupção da gpio habilitada
    gpio_set_irq_enabled_with_callback(
        button_0, GPIO_IRQ_EDGE_FALL, 1, &gpio_irq_handler
    );

    long unsigned int frames = sizeof(movie) / sizeof(movie[0]);

    while (true) {
        animate(movie, frames, 200);
    }
}
