#include "gpio.h"

void GPIO_On(unsigned short int pin, GPIO_Function_Select mode)
{
    if (pin > 53) return;
    GPIO *gpio = (GPIO*)GPIO_BASE;

    unsigned short int pinSet = pin / 10;
    unsigned short int pinNumber = (pin % 10) * 3;

    gpio->FunctionSelect[pinSet] = (mode << pinNumber);
}

void GPIO_GPPUD_SET(unsigned char flag)
{
    if (flag > 2) return;
    GPIO *gpio = (GPIO*)GPIO_BASE;
    gpio->PinPullUpDownEnable = flag;
}

void GPIO_GPPUDCLK0_SET(unsigned short int line)
{
    if (line > 53) return;
    GPIO *gpio = (GPIO*)GPIO_BASE;
    unsigned int i = line / 32;
    line %= 32;
    gpio->PinPullUpDownEnableClock[i] |= (1 << line);
}

void GPIO_SetPin(unsigned short int pin)
{
    if (pin > 53) return;
    GPIO *gpio = (GPIO*)GPIO_BASE;
    unsigned int i = pin / 32;
    pin %= 32;
    gpio->OutputSet[i] |= (1 << pin);
}

unsigned int GPIO_ReadPin(unsigned char pin)
{
    unsigned int pinOn;
    unsigned int test;

    if (pin > 53) return -1;
    GPIO *gpio = (GPIO*)GPIO_BASE;
    unsigned int i = pin / 32;
    pin %= 32;
    pinOn = 1 << pin;
    test = gpio->PinLevel[i] & pinOn;
    return (test >> pin);
}

void GPIO_ClearPin(unsigned short int pin)
{
    if (pin > 53) return;
    GPIO *gpio = (GPIO*)GPIO_BASE;
    unsigned int i = pin / 32;
    pin %= 32;
    gpio->OutputClear[i] |= (1 << pin);
}
