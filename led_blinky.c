/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "app.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DOT_MS        500U
#define DASH_MS       1000U
#define SYM_GAP_MS    500U
#define LETTER_GAP_MS 2000U
#define WORD_GAP_MS   4000U

#define DOT  0
#define DASH 1
#define END  255

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void delay_ms(uint32_t ms);
void led_on(void);
void led_off(void);
void morse_send_letter(const uint8_t *symbols);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_msCounter = 0;

const uint8_t morse_S[] = {DOT, DOT, DOT, END};
const uint8_t morse_A[] = {DOT, DASH, END};
const uint8_t morse_L[] = {DOT, DASH, DOT, DOT, END};
const uint8_t morse_U[] = {DOT, DOT, DASH, END};
const uint8_t morse_T[] = {DASH, END};

const uint8_t *morse_SALUT[] = {morse_S, morse_A, morse_L, morse_U, morse_T};

#define NUM_LETTERS 5

/*******************************************************************************
 * Code
 ******************************************************************************/
void SysTick_Handler(void)
{
    g_msCounter++;
}

void delay_ms(uint32_t ms)
{
    uint32_t start = g_msCounter;
    while ((g_msCounter - start) < ms)
    {
    }
}

void led_on(void)
{
    GPIO_PinWrite(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, LOGIC_LED_ON);
}

void led_off(void)
{
    GPIO_PinWrite(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, LOGIC_LED_OFF);
}

void morse_send_letter(const uint8_t *symbols)
{
    for (uint8_t i = 0; symbols[i] != END; i++)
    {
        led_on();
        if (symbols[i] == DOT)
            delay_ms(DOT_MS);
        else
            delay_ms(DASH_MS);
        led_off();


        if (symbols[i + 1] != END)
            delay_ms(SYM_GAP_MS);
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Board pin init */
    BOARD_InitHardware();


    SysTick_Config(12000UL);

    LED_RED_INIT(LOGIC_LED_OFF);

    while (1)
    {
        for (uint8_t i = 0; i < NUM_LETTERS; i++)
        {
            morse_send_letter(morse_SALUT[i]);
            delay_ms(LETTER_GAP_MS);
        }

        delay_ms(WORD_GAP_MS);
    }
}
