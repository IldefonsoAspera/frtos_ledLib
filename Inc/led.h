#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "stm32g0xx_hal.h"


typedef struct
{
    bool          isSlotInUse;
    bool          enabled;
    bool          isAligned;
    bool          isInverted;     // Declares if output is inverted (active low)
    bool          isPWM;          // Identifies the pattern as GPIO ON-OFF or TIMER PWM
    uint8_t       patNum;         // LED pattern ID. If there are 14 different ones, 0-13
    uint8_t       patIdx;         // PWM value index. If a pattern has 50 duty cycle values, 0-49
    GPIO_TypeDef *GPIOx;
    uint16_t      GPIO_Pin;
} led_t;


#define LED_CFG_GPIO(pattern, gpioPort, gpioPin, inverted)  \
{.isSlotInUse = true, .enabled = true, .isAligned = false, .isInverted = (inverted), \
 .isPWM = false, .patNum = (pattern), .patIdx = 0, .GPIOx = (gpioPort), .GPIO_Pin = (gpioPin)}



uint8_t led_start(led_t *pLed_cfg);
void led_pause(uint8_t idx);
void led_resume(uint8_t idx);
void led_stop(uint8_t idx);
void led_thread(void const * argument);
void led_init();







#ifdef  __cplusplus
}
#endif


#endif
