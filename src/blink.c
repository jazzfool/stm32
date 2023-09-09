/*
    blink.c - jazzfool, 2023

    toggles the blue LED (LD2) once every second
        using SysTick interrupts.
*/

#include <hal2/gpio.h>
#include <hal2/rcc.h>
#include <hal2/systick.h>

#define LD2 (PIN('B', 7))

#define SYSTICK_HANDLER
void systick_handler(void)
{
    gpio_write(LD2, !gpio_read_odr(LD2));
}

#include <hal2/nohandlers.h>

int main(void)
{
    RCC->AHB1ENR |= BIT(PINBANK(LD2));

    gpio_set_mode(LD2, GPIO_MODER_OUTPUT);
    gpio_write(LD2, 0);

    /* 10ms * 100 = 1s */
    const uint32_t tenms = systick_read_calib_tenms();
    systick_set_reload_value(tenms * 100);
    systick_set_tickint(1);
    systick_set_enable(1);
    systick_set_clksource(0);

    for (;;)
        (void)0;
}
