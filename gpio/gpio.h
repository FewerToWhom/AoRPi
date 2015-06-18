#ifndef GPIO_H
#define GPIO_H

#define GPIO_BASE 0x20200000

struct GPIO_t {
    unsigned int FunctionSelect[6];
    unsigned int reserved1;
    unsigned int OutputSet[2];
    unsigned int reserved2;
    unsigned int OutputClear[2];
    unsigned int reserved3;
    unsigned int PinLevel[2];
    unsigned int reserved4;
    unsigned int EventDetectStatus[2];
    unsigned int reserved5;
    unsigned int RisingEdgeDetectEnable[2];
    unsigned int reserved6;
    unsigned int FallingEdgeDetectEnable[2];
    unsigned int reserved7;
    unsigned int PinHighDetectEnable[2];
    unsigned int reserved8;
    unsigned int PinLowDetectEnable[2];
    unsigned int reserved9;
    unsigned int PinAsyncRisingEdgeDetect[2];
    unsigned int reserved10;
    unsigned int PinAsyncFallingEdgeDetect[2];
    unsigned int reserved11;
    unsigned int PinPullUpDownEnable;
    unsigned int PinPullUpDownEnableClock[2];
    unsigned int reserved12[4];
    unsigned char Test;
    unsigned char padding[3];
};

typedef volatile struct GPIO_t GPIO;

typedef enum {INPUT, OUTPUT, AF0, AF1, AF2, AF3, AF4, AF5} GPIO_Function_Select;

void GPIO_On(unsigned short int pin, GPIO_Function_Select mode);
void GPIO_SetPin(unsigned short int pin);
void GPIO_ClearPin(unsigned short int pin);
unsigned int GPIO_ReadPin(unsigned char pin);

void GPIO_GPPUD_SET(unsigned char flag);
void GPIO_GPPUDCLK0_SET(unsigned short int line);
void GPIO_GPPUDCLK0_CLEAR(unsigned short int line);

#endif
