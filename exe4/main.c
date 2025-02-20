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

  while (true) {
  }
}
