#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>
const int BTN_PIN_R;
const int BTN_PIN_G;
const int LED_PIN_R;
const int LED_PIN_G;
volatile int BTN_FLAG_R;
volatile int BTN_FLAG_G;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    if (gpio == BTN_PIN_R)
      BTN_FLAG_R = 1;
    else if (gpio == BTN_PIN_G)
      BTN_FLAG_G = 1;
  }
}

int main() {
  stdio_init_all();
  gpio_init(BTN_PIN_R);
  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(LED_PIN_G);
  gpio_init(LED_PIN_R);
  gpio_set_dir(LED_PIN_G, GPIO_OUT);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);

  while (true) {
    if (BTN_FLAG_R){
      gpio_put(LED_PIN_R, !gpio_get(LED_PIN_R));
      BTN_FLAG_R = 0;
    }
    if (BTN_FLAG_G){
      gpio_put(LED_PIN_G, !gpio_get(LED_PIN_G));
      BTN_FLAG_G = 0;
    }
  }
}
