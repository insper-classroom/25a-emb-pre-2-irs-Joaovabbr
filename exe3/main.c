#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;
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
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  // callback led r (first)
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true,
                                     &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_FALL, true);

  while (true) {

    if(BTN_FLAG_R){
      printf("fall red\n");
      sleep_ms(150);
      BTN_FLAG_R = 0;
    }
    if(BTN_FLAG_G){
      printf("fall green\n");
      sleep_ms(150);
      BTN_FLAG_G = 0;
    }
  }
}
