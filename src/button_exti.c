/*
    button_exti.c - jazzfool, 2023

    PB7 = LD2 (blue LED)
    PC13 = B1 (blue button)

    lights up the blue LED while the blue button is pressed.
*/

#include <hal2/gpio.h>
#include <hal2/rcc.h>
#include <hal2/nvic.h>
#include <hal2/exti.h>

#define LD2 (PIN('B', 7))
#define B1 (PIN('C', 13))

#define EXTI15_10_HANDLER
void exti15_10_handler(void)
{
    if (EXTI->PR & BIT(13)) {
        gpio_write(LD2, gpio_read(B1));
    }
    exti_clear_pr(13);
}

#include <hal2/nohandlers.h>

int main(void)
{
    RCC->AHB1ENR |= BIT(PINBANK(LD2));
    RCC->AHB1ENR |= BIT(PINBANK(B1));

    nvic_set_enable_interrupt(40);

    /* LD2 output */
    /* B1 input */
    gpio_set_mode(LD2, GPIO_MODER_OUTPUT);
    gpio_set_mode(B1, GPIO_MODER_INPUT);

    /* turn off LD2 */
    gpio_write(LD2, 0);

    /* interrupt on rising+falling edge of EXTI13 */
    exti_set_imr(13, 1);
    exti_set_rtsr(13, 1);
    exti_set_ftsr(13, 1);
}
