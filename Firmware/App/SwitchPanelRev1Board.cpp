#include "BrytecBoard.h"

#include "CanBus.h"
#include "Fram.h"
#include "FramDeserializer.h"
#include "SwitchPanelRev1Defs.h"
#include "Usb.h"
#include "Ws2812.h"
#include "gpio.h"

namespace Brytec {

FramDeserializer deserializer;

BinaryDeserializer* BrytecBoard::getDeserializer()
{
    FramDeserializer des;
    deserializer = des;
    return &deserializer;
}

void BrytecBoard::error(EBrytecErrors error)
{
    switch (error) {
    case EBrytecErrors::ModuleHeader:
        printf("Module header is wrong\n");
        break;
    case EBrytecErrors::NodeGroupHeader:
        printf("Node Group header is wrong\n");
        break;
    case EBrytecErrors::ModuleNotEnabled:
        printf("This module is not enabled\n");
        break;
    case EBrytecErrors::AddNodeFailed:
        printf("Failed to add node\n");
        break;
    case EBrytecErrors::NodeVectorOutOfSpace:
        printf("Node Vector out of space\n");
        break;
    case EBrytecErrors::FailedToCreateNode:
        printf("Failed to create node\n");
        break;
    case EBrytecErrors::NodeIndexOutOfBounds:
        printf("Node index out of bounds\n");
        break;
    case EBrytecErrors::BadAlloc:
        printf("Node group allocation failed\n");
        break;
    case EBrytecErrors::CanBufferFull:
        printf("Can Buffer Full\n");
        break;

    default:
        printf("Unknown Error\n");
        break;
    }
}

void BrytecBoard::setupBrytecCan(uint32_t mask, uint32_t filter)
{
}

void BrytecBoard::setupPin(uint16_t index, IOTypes::Types type)
{
}

void BrytecBoard::shutdownAllPins()
{
    Ws2812::setAll(0, 0, 0);
}

float BrytecBoard::getPinValue(uint16_t index, IOTypes::Types type)
{
    switch (index) {
    case BT_PIN_Button_1:
        return !HAL_GPIO_ReadPin(Sw8_GPIO_Port, Sw8_Pin);
    case BT_PIN_Button_2:
        return !HAL_GPIO_ReadPin(Sw5_GPIO_Port, Sw5_Pin);
    case BT_PIN_Button_3:
        return !HAL_GPIO_ReadPin(Sw4_GPIO_Port, Sw4_Pin);
    case BT_PIN_Button_4:
        return !HAL_GPIO_ReadPin(Sw1_GPIO_Port, Sw1_Pin);
    case BT_PIN_Button_5:
        return !HAL_GPIO_ReadPin(Sw7_GPIO_Port, Sw7_Pin);
    case BT_PIN_Button_6:
        return !HAL_GPIO_ReadPin(Sw6_GPIO_Port, Sw6_Pin);
    case BT_PIN_Button_7:
        return !HAL_GPIO_ReadPin(Sw3_GPIO_Port, Sw3_Pin);
    case BT_PIN_Button_8:
        return !HAL_GPIO_ReadPin(Sw2_GPIO_Port, Sw2_Pin);

    default:
        break;
    }

    return 0.0f;
}

float BrytecBoard::getPinVoltage(uint16_t index)
{

    return 0.0f;
}

float BrytecBoard::getPinCurrent(uint16_t index)
{

    return 0.0f;
}

void BrytecBoard::setPinValue(uint16_t index, IOTypes::Types type, float value)
{
    if (index >= BT_PIN_Light_1 && index <= BT_PIN_Light_8) {

        uint32_t color = (uint32_t)value;
        uint8_t r = color & 0xFF;
        uint8_t g = (color >> 8) & 0xFF;
        uint8_t b = (color >> 16) & 0xFF;

        switch (index) {
        case BT_PIN_Light_1:
            Ws2812::setPixel(7, r, g, b);
            break;
        case BT_PIN_Light_2:
            Ws2812::setPixel(4, r, g, b);
            break;
        case BT_PIN_Light_3:
            Ws2812::setPixel(3, r, g, b);
            break;
        case BT_PIN_Light_4:
            Ws2812::setPixel(0, r, g, b);
            break;
        case BT_PIN_Light_5:
            Ws2812::setPixel(6, r, g, b);
            break;
        case BT_PIN_Light_6:
            Ws2812::setPixel(5, r, g, b);
            break;
        case BT_PIN_Light_7:
            Ws2812::setPixel(2, r, g, b);
            break;
        case BT_PIN_Light_8:
            Ws2812::setPixel(1, r, g, b);
            break;

        default:
            break;
        }
    }
}

void BrytecBoard::sendBrytecCan(const CanExtFrame& frame)
{
    CanBus::send(frame);
}

void BrytecBoard::sendBrytecCanUsb(const CanExtFrame& frame)
{
    Brytec::UsbPacket packet;
    packet.set<Brytec::CanExtFrame>(frame);
    Usb::send(packet);
}

void BrytecBoard::ReserveConfigSize(uint16_t size)
{
    Fram::write(0, (uint8_t*)&size, 2);
}

void BrytecBoard::updateConfig(uint8_t* data, uint32_t size, uint32_t offset)
{
    // Add room for storing the size
    Fram::write(offset + 2, data, size);
}

uint32_t BrytecBoard::getTemplateSize()
{
    return sizeof(moduleTemplate);
}

void BrytecBoard::getTemplateData(uint8_t* dest, uint32_t offset, uint32_t length)
{
    if (offset > sizeof(moduleTemplate))
        return;

    memcpy(dest, &moduleTemplate[offset], length);
}

uint32_t BrytecBoard::getConfigSize()
{
    uint16_t dataSize;
    Fram::read(0, (uint8_t*)&dataSize, 2);
    return dataSize;
}

void BrytecBoard::getConfigData(uint8_t* dest, uint32_t offset, uint32_t length)
{
    Fram::read(offset + 2, dest, length);
}
}