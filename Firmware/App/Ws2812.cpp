#include "Ws2812.h"

#include "main.h"
#include "stdio.h"
#include "tim.h"
#include <string.h>

extern DMA_HandleTypeDef hdma_tim1_ch3;

#define PWM_HI (115)
#define PWM_LO (57)

#define WS2812_NUM_LEDS 8
#define WS2812_RESET_PULSE 64
#define WS2812_BUFFER_SIZE (WS2812_NUM_LEDS * 24 + WS2812_RESET_PULSE)

uint8_t ws2812_buffer[WS2812_BUFFER_SIZE] = {};

#define WS2812_FILL_BUFFER(COLOR)                 \
    for (uint8_t mask = 0x80; mask; mask >>= 1) { \
        if (COLOR & mask) {                       \
            *ptr++ = PWM_HI;                      \
        } else {                                  \
            *ptr++ = PWM_LO;                      \
        }                                         \
    }

void Ws2812::init()
{
    memset(ws2812_buffer, 0, WS2812_BUFFER_SIZE);
    setAll(0, 0, 0);
    HAL_TIMEx_PWMN_Start_DMA(&htim1, TIM_CHANNEL_3, (uint32_t*)ws2812_buffer, WS2812_BUFFER_SIZE);
}

void Ws2812::setPixel(uint16_t index, uint8_t r, uint8_t g, uint8_t b)
{
    if (index >= WS2812_NUM_LEDS)
        return;

    uint8_t* ptr = &ws2812_buffer[24 * index];
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
