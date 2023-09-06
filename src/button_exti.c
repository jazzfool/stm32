#include <stm32f756xx.h>
#include <stm32f7xx_hal_conf.h>

/*
    button_exti.c - jazzfool, 2023

    PB7 = LD2 (blue LED)
    PC13 = B1 (blue button)

    lights up the blue LED while the blue button is pressed.
*/

void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR & EXTI_PR_PR13) {
        /* is B1 pressed? */
        if (GPIOC->IDR & (1 << 13)) {
            /* turn on LD1 */
            GPIOB->ODR = (1 << 7);
        } else {
            /* turn off LD1 */
            GPIOB->ODR = 0;
        }
    }

    /* reset EXTI pending register */
    EXTI->PR = 0x0;
}

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    /* EXTI13 IRQ */
    NVIC->ISER[1] = (1 << (EXTI15_10_IRQn - 32));

    /* PB7 output */
    GPIOB->MODER = (1 << 14);

    /* PC13 input */
    GPIOC->MODER = 0;

    /* turn off LD1 */
    GPIOB->ODR = 0;

    /* enable EXTI13 interrupt mask */
    EXTI->IMR |= (1 << 13);

    /* enable EXTI13 rising and falling edge detection */
    EXTI->RTSR |= (1 << 13);
    EXTI->FTSR |= (1 << 13);
}
