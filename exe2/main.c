#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>
const int BTN_PIN = 28;
const int LED_PIN = 4;
volatile int BTN_FLAG;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    BTN_FLAG = 1;
  } else if (events == 0x8) { // rise edge
    BTN_FLAG = 0;
  }
}


int main() {
  stdio_init_all();
  gpio_init(BTN_PIN);
  gpio_set_dir(BTN_PIN, GPIO_IN);
  gpio_pull_up(BTN_PIN);

  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_set_irq_enabled_with_callback(BTN_PIN,GPIO_IRQ_EDGE_FALL|GPIO_IRQ_EDGE_RISE,true, &btn_callback);
  while (true) {
    if (BTN_FLAG){
      gpio_put(LED_PIN, 1);
    }else{
      gpio_put(LED_PIN, 0);
    }
  }
}
