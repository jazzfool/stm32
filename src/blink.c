#include <stm32f7xx_hal_conf.h>

/*
    blink.c - jazzfool, 2023

    toggles the blue LED (LD2) once every 2-3 seconds
        using TIM2 and NVIC IRQ handlers.
*/

void TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF) {
        /* toggle PB7 */
        GPIOB->ODR ^= (1 << 7);
    }
    /* reset TIM2 status register */
    TIM2->SR = 0x0;
}

int main(void)
{
    /* enable GPIOB and TIM2 */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* PB7 output */
    GPIOB->MODER = (1 << 14);

    /* TIM2 IRQ */
    NVIC->ISER[0] |= 1 << TIM2_IRQn;

    /* TIM2 counter */
    TIM2->PSC = 0x7D00; /* 1/32000 clock */
    TIM2->DIER = TIM_DIER_UIE;
    TIM2->ARR = 0x3E8; /* count up to 1000 */
    TIM2->CR1 = TIM_CR1_ARPE | TIM_CR1_CEN;
    TIM2->EGR = 1;

    while (1)
        ;
}
