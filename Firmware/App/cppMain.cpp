#include "cppMain.h"

#include "CanBus.h"
#include "EBrytecApp.h"
#include "Fram.h"
#include "MsTimeout.h"
#include "UsDelay.h"
#include "Usb.h"
#include "Ws2812.h"
#include "stm32g4xx_hal.h"
#include <stdint.h>

MsTimeout brytecMs(10);
// bool lastIgntionPowerState = false;

void cppMain()
{
    Fram::init(&hspi1);

    Brytec::EBrytecApp::initalize();

    if (Brytec::EBrytecApp::isDeserializeOk())
        printf("Deserialize Ok\n");
    else
        printf("Deserialize FAIL\n");

    Ws2812::init();

    while (1) {

        Usb::update();

        Brytec::EBrytecApp::processCanCommands();

        if (brytecMs.isTimeout())
            Brytec::EBrytecApp::update(brytecMs.getTimestepMs());
    }
}