#include <pico/stdlib.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define BUZZER_PIN 21

#define BUZZER_A 21
#define BUZZER_B 10

// Função para configurar o PWM no pino do buzzer
void setup_buzzer(uint gpio_pin, uint32_t frequency) {
    // Escolher o slice do PWM baseado no pino GPIO
    uint slice_num = pwm_gpio_to_slice_num(gpio_pin);

    // Conectar o pino GPIO ao PWM
    pwm_set_gpio_level(gpio_pin, 0);
    gpio_set_function(gpio_pin, GPIO_FUNC_PWM);

    // Calcular o divisor do clock para atingir a frequência desejada
    uint32_t clock_div = clock_get_hz(clk_sys) / (frequency * 65536);
    pwm_set_clkdiv(slice_num, clock_div);

    // Configurar o PWM para rodar no modo de contagem padrão
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_div);

    // Aplicar a configuração ao slice
    pwm_init(slice_num, &config, true);
}

// Função para tocar uma nota (determinar frequência e duty cycle)
void play_buzzer(uint gpio_pin, uint32_t frequency, float duty_cycle) {
    uint slice_num = pwm_gpio_to_slice_num(gpio_pin);

    // Configurar o divisor do clock novamente para ajustar a frequência
    uint32_t clock_div = clock_get_hz(clk_sys) / (frequency * 65536);
    pwm_set_clkdiv(slice_num, clock_div);

    // Ajustar o nível do duty cycle
    uint16_t level = (uint16_t)(duty_cycle * 65535);
    pwm_set_gpio_level(gpio_pin, level);
}

// Função para parar o buzzer
void stop_buzzer(uint gpio_pin) {
    // Duty cycle em 0
    pwm_set_gpio_level(gpio_pin, 0); 
}

void run_buzzer(uint32_t frequency) {
    // Tocar a nota com 50% de duty cycle
    play_buzzer(BUZZER_PIN, frequency, 0.5);
    // Toca por 500ms
    sleep_ms(500); 

    // Parar o buzzer
    stop_buzzer(BUZZER_PIN);
    // Pausa de 500ms
    sleep_ms(500); 
}
