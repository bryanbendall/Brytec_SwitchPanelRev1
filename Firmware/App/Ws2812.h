#pragma once

// Originally from
// https://www.newinnovations.nl/post/controlling-ws2812-and-ws2812b-using-only-stm32-spi/
// and
// https://www.thevfdcollective.com/blog/stm32-and-sk6812-rgbw-led

#include "spi.h"

class Ws2812 {

public:
    static void init();
    static void setPixel(uint16_t index, uint8_t r, uint8_t g, uint8_t b);
    static void setAll(uint8_t r, uint8_t g, uint8_t b);
};