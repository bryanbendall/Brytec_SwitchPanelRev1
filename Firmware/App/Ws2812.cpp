#include "Ws2812.h"
#include "main.h"
#include <string.h>

#define WS2812_NUM_LEDS 8
#define WS2812_RESET_PULSE 60
#define WS2812_BUFFER_SIZE (WS2812_NUM_LEDS * 24 + WS2812_RESET_PULSE)

uint8_t ws2812_buffer[WS2812_BUFFER_SIZE] = {};

#define WS2812_FILL_BUFFER(COLOR)                 \
    for (uint8_t mask = 0x80; mask; mask >>= 1) { \
        if (COLOR & mask) {                       \
            *ptr++ = 0xfc;                        \
        } else {                                  \
            *ptr++ = 0x80;                        \
        }                                         \
    }

void Ws2812::init()
{
    // change for dma
    // HAL_SPI_Transmit_DMA(&hspi2, ws2812_buffer, WS2812_BUFFER_SIZE);
    // have to set in interrupt handler

    send();
}

void Ws2812::send()
{
    HAL_SPI_Transmit(&hspi2, ws2812_buffer, WS2812_BUFFER_SIZE, HAL_MAX_DELAY);
}

void Ws2812::setPixel(uint16_t led, uint8_t r, uint8_t g, uint8_t b)
{
    uint8_t* ptr = &ws2812_buffer[24 * led];
    WS2812_FILL_BUFFER(g);
    WS2812_FILL_BUFFER(r);
    WS2812_FILL_BUFFER(b);
}

void Ws2812::setAll(uint8_t r, uint8_t g, uint8_t b)
{
    uint8_t* ptr = ws2812_buffer;
    for (uint16_t i = 0; i < WS2812_NUM_LEDS; ++i) {
        WS2812_FILL_BUFFER(g);
        WS2812_FILL_BUFFER(r);
        WS2812_FILL_BUFFER(b);
    }
}