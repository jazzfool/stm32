/*
    print_uart.c - jazzfool, 2023

    PD8 = USART3 TX
    PD9 = USART3 RX

    sends a message over USART3 (virtual COM port)
        every time the blue button (B1) is pressed
*/

#include <hal2/exti.h>
#include <hal2/gpio.h>
#include <hal2/nvic.h>
#include <hal2/rcc.h>
#include <hal2/uart.h>

#define B1 (PIN('C', 13))
#define USART3_TX (PIN('D', 8))
#define USART3_RX (PIN('D', 9))

#include <hal2/nohandlers.h>

int main(void)
{
    RCC->AHB1ENR |= BIT(PINBANK(USART3_TX));
    RCC->AHB1ENR |= BIT(PINBANK(B1));
    RCC->APB1ENR |= BIT(18);

    USART3->CR1 = 0;
    usart_set_baud_rate(USART3, 115200);
    usart_set_tx_enabled(USART3, 1);
    usart_set_rx_enabled(USART3, 1);
    usart_set_usart_enabled(USART3, 1);

    gpio_set_mode(USART3_TX, GPIO_MODER_AF);
    gpio_set_mode(USART3_RX, GPIO_MODER_AF);
    gpio_set_af(USART3_TX, 7);
    gpio_set_af(USART3_RX, 7);

    gpio_set_mode(B1, GPIO_MODER_INPUT);

    uint8_t press = gpio_read(B1);
    for (;;) {
        uint8_t b1 = gpio_read(B1);
        if (press != b1) {
            press = b1;
            if (b1) {
                char* msg = "Hello, world!\r\n";
                for (; *msg != 0; ++msg) {
                    usart_write_byte(USART3, *msg);
                    while (!usart_read_txe(USART3))
                        (void)0;
                }
            }
        }
    }
}