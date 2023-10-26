#pragma once

// Originally from
// https://www.newinnovations.nl/post/controlling-ws2812-and-ws2812b-using-only-stm32-spi/

#include "spi.h"

class Ws2812 {

public:
    static void init();
    static void send();
    static void setPixel(uint16_t led, uint8_t r, uint8_t g, uint8_t b);
    static void setAll(uint8_t r, uint8_t g, uint8_t b);
};