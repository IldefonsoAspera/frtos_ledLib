#include "led.h"

#include <stdint.h>
#include <stdbool.h>

#include "stm32g0xx_hal.h"
#include "cmsis_os.h"

#define LED_N_LEDS      5
#define LED_ALL_ALIGNED 0


#define LED_NO_SLOT_AVAILABLE   UINT8_MAX
#define LED_PWM_CYCLE_DUR_MS    100
#define LED_ARRAY_N_ELEM(x)     sizeof(x)/(sizeof(x)[0])





static const uint8_t ledPattern[2][10] =
{
    {255, 0, 255, 0, 0, 0, 0, 0, 0, 0},
    {255, 255, 255, 255, 255, 0, 0, 0, 0, 0},
};


static led_t led[LED_N_LEDS] = {0};


uint8_t led_start(led_t *pLed_cfg)
{
    for(int i = 0; i < LED_ARRAY_N_ELEM(led); i++)
    {
        if(!led[i].isSlotInUse)
        {
            led[i] = *pLed_cfg;
            HAL_GPIO_WritePin(led[i].GPIOx, led[i].GPIO_Pin, led[i].isInverted);
            return i;
        }
    }
    return LED_NO_SLOT_AVAILABLE;
}


void led_pause(uint8_t idx)
{
    if(idx < LED_ARRAY_N_ELEM(led))
        led[idx].enabled = false;
}


void led_resume(uint8_t idx)
{
    if(idx < LED_ARRAY_N_ELEM(led))
        led[idx].enabled = true;
}


void led_stop(uint8_t idx)
{
    if(idx < LED_ARRAY_N_ELEM(led))
    {
        led[idx].isSlotInUse = false;
        HAL_GPIO_WritePin(led[idx].GPIOx, led[idx].GPIO_Pin, led[idx].isInverted);
    }
}


void led_thread(void const * argument)
{

    while (1)
    {
        for(int i = 0; i < LED_ARRAY_N_ELEM(led); i++)
        {
            if(led[i].isSlotInUse && led[i].enabled)
            {
                if(led[i].isPWM)
                {
                    // TODO
                }
                else
                {
                    bool onOff = ledPattern[led[i].patNum][led[i].patIdx] > UINT8_MAX/2;
                    led[i].patIdx = (led[i].patIdx + 1) % LED_ARRAY_N_ELEM(ledPattern[0]);
                    HAL_GPIO_WritePin(led[i].GPIOx, led[i].GPIO_Pin, onOff);
                }
            }
        }
        osDelay(LED_PWM_CYCLE_DUR_MS);
    }
}


void led_init()
{

}
