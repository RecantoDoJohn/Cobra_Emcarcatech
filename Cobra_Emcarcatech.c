#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"

#include "cobra.h"
#include "fruta.h"

#include "ws2818b.pio.h"

#define LED_COUNT 25
#define LED_PIN 7

#define ADC_MAX 4095
#define DEADZONE 500  


// Definição de pixel GRB
struct pixel_t {
  uint8_t G, R, B; 
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; 

// Declaração do buffer de pixels que formam a matriz.
npLED_t leds[LED_COUNT];


PIO np_pio;
uint sm;


void npInit(uint pin) {

  // Cria programa PIO.
  uint offset = pio_add_program(pio0, &ws2818b_program);
  np_pio = pio0;

  // Toma posse de uma máquina PIO.
  sm = pio_claim_unused_sm(np_pio, false);
  if (sm < 0) {
    np_pio = pio1;
    sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
  }

  // Inicia programa na máquina PIO obtida.
  ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

  // Limpa buffer de pixels.
  for (uint i = 0; i < LED_COUNT; ++i) {
    leds[i].R = 1;
    leds[i].G = 1;
    leds[i].B = 1;
  }
}

/**
 * Atribui uma cor RGB a um LED.
 */
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
  leds[index].R = r;
  leds[index].G = g;
  leds[index].B = b;
}

/**
 * Limpa o buffer de pixels.
 */
void npClear() {
  for (uint i = 0; i < LED_COUNT; ++i)
    npSetLED(i, 0, 0, 0);
}


void npWrite() {
  for (uint i = 0; i < LED_COUNT; ++i) {
    pio_sm_put_blocking(np_pio, sm, leds[i].G);
    pio_sm_put_blocking(np_pio, sm, leds[i].R);
    pio_sm_put_blocking(np_pio, sm, leds[i].B);
  }
  sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}


int getIndex(int x, int y) {
    if (y % 2 == 0) {
        return 24-(y * 5 + x); 
    } else {
        return 24-(y * 5 + (4 - x)); 
    }
}



void detectar_direcao(uint16_t x, uint16_t y, struct cobraCompleta* cobra) {
  uint16_t centro = ADC_MAX / 2;

  if (y > centro + DEADZONE) {
    cobra->direcao = 3;
  }
  if (y < centro - DEADZONE) {
    cobra->direcao = 1;
  }
  if (x > centro + DEADZONE) {
    cobra->direcao = 0;
  }
  if (x < centro - DEADZONE) {
    cobra->direcao = 2;
  }

}

void verificarComida(struct cobraCompleta* cobra, struct fruta *fruta ) {
    if (cobra->cobraPedaco[0]->x == fruta->x && cobra->cobraPedaco[0]->y == fruta->y ) {
        crescer(cobra);
        gerarFruta(fruta, cobra);
    }

}


int main() {



  // Inicializa entradas e saídas.
  stdio_init_all();
  adc_init();

  adc_gpio_init(26);
  adc_gpio_init(27);

  
  npInit(LED_PIN);
  npClear();

  struct cobraCompleta cobra;
  inicializarCobra(&cobra);

  struct fruta fruta;
  gerarFruta(&fruta, &cobra);
  
while (true) {
  adc_select_input(0);           
  uint adc_y_raw = adc_read();   

  adc_select_input(1);           
  uint adc_x_raw = adc_read();   

  detectar_direcao(adc_x_raw, adc_y_raw, &cobra);

  verificarComida(&cobra, &fruta);


    npClear();
    npSetLED(getIndex(fruta.x, fruta.y), 25, 0, 30);


    mover(&cobra);
    for (int i = 0; i < cobra.tamanho; i++) {
      npSetLED(getIndex(cobra.cobraPedaco[i]->x, cobra.cobraPedaco[i]->y), 25, 25, 0);
    } 

    npWrite();
    sleep_ms(750);
  }
}
