#include <stdio.h>

// Inclui a biblioteca padrão para funcionalidades básicas como GPIO, temporização e comunicação serial.
#include "pico/stdlib.h"
// Inclui a biblioteca para gerenciamento de temporizadores de hardware.
#include "hardware/timer.h"

#include "traffic_light/traffic_light.h"

uint traffic_light_state = 0;

// Função de callback que será chamada repetidamente pelo temporizador.
// O tipo bool indica que a função deve retornar verdadeiro ou falso
// para continuar ou parar o temporizador.
bool repeating_timer_callback(struct repeating_timer *t) {
    // Imprime uma mensagem na saída serial indicando que algum tempo se passou.
    printf("3 segundos se passaram\n");

    traffic_light_state = ++traffic_light_state % 3;
    if(traffic_light_state == 0) {
        set_red();
    } else if(traffic_light_state == 1) {
        set_yellow();
    } else if(traffic_light_state == 2) {
        set_green();
    }
    // Retorna true para manter o temporizador repetindo.
    return true;
}

int main()
{
    stdio_init_all();
    setup_traffic_light();
    set_red();

    // Declaração de uma estrutura de temporizador de repetição.
    // Esta estrutura armazenará informações sobre o temporizador configurado.
    struct repeating_timer timer;

    // Configura o temporizador para chamar a função de callback a cada 3 segundos.
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
        // Pausa de 10 segundos para reduzir o uso da CPU.
        sleep_ms(10000);
        printf("rotina de repetição\n");
    }
}
