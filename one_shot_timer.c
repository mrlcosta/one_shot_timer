#include "pico/stdlib.h"
#include "pico/time.h"

// Definindo os pinos dos LEDs
#define LED_GREEN  11
#define LED_BLUE   12
#define LED_RED    13

// Definindo o pino do botão
#define BUTTON_PIN 5

// Estado dos LEDs
enum led_state { ALL_ON, ONE_ON, OFF };
static enum led_state estado_led = OFF;

// Variável para indicar se o botão foi pressionado
volatile bool leds_active = false;

// Função de callback do temporizador
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    switch (estado_led) {
        case ALL_ON:
            gpio_put(LED_GREEN, 1);
            gpio_put(LED_BLUE, 0);
            gpio_put(LED_RED, 1);
            estado_led = ONE_ON;
            add_alarm_in_ms(3000, turn_off_callback, NULL, false); // One-shot alarm
            break;
        case ONE_ON:
            gpio_put(LED_GREEN, 1);
            gpio_put(LED_BLUE, 0);
            gpio_put(LED_RED, 0);
            estado_led = OFF;
            add_alarm_in_ms(3000, turn_off_callback, NULL, false); // One-shot alarm
            break;
        case OFF:
            gpio_put(LED_GREEN, 0);
            gpio_put(LED_BLUE, 0);
            gpio_put(LED_RED, 0);
            leds_active = false;
            break;
    }
    return 0;
}

void button_irq_callback(uint gpio, uint32_t events) {
    if (!leds_active) {
        leds_active = true;
        gpio_put(LED_BLUE, 1);
        gpio_put(LED_RED, 1);
        gpio_put(LED_GREEN, 1);
        estado_led = ALL_ON;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    }
}

int main() {
    stdio_init_all();

    // Configura os pinos dos LEDs como saída
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);

    // Configura o pino do botão como entrada com resistor de pull-up
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // Configura o evento de interrupção para o botão (detectar a pressão)
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_irq_callback);

    // Loop principal
    while (true) {
        sleep_ms(10); 
    }

    return 0;
}
