extern int main(void);
extern void systick_handler(void);
extern void exti15_10_handler(void);

__attribute((naked, noreturn)) void _reset_handler(void)
{
    /* defined by ld */
    extern long _sbss, _ebss, _sdata, _edata, _sidata;
    for (long* p = &_sbss; p < &_ebss; ++p)
        *p = 0;
    for (long *pdst = &_sdata, *psrc = &_sidata; pdst < &_edata;)
        *pdst++ = *psrc++;

    main();
    for (;;)
        (void)0;
}

/* forward decl fn for vtab */
/* takes places of initial stack ptr */
/* see linker script */
extern void _estack(void);

__attribute__((section(".vectors"))) void (*const vtab[16 + 91])(void) = {
    /* Initial SBP */ _estack,
    /* Reset */ _reset_handler,
    /* NMI */ 0,
    /* HardFault */ 0,
    /* MemManage */ 0,
    /* BusFault */ 0,
    /* UsageFault */ 0,
    /* Reserved */ 0,
    /* Reserved */ 0,
    /* Reserved */ 0,
    /* Reserved */ 0,
    /* SVCall */ 0,
    /* Debug Monitor */ 0,
    /* Reserved */ 0,
    /* PendSV */ 0,
    /* SysTick */ systick_handler,
    /* WWDG */ 0,
    /* PVD */ 0,
    /* TAMP_STAMP */ 0,
    /* RTC_WKUP */ 0,
    /* FLASH */ 0,
    /* RCC */ 0,
    /* EXTI0 */ 0,
    /* EXTI1 */ 0,
    /* EXTI2 */ 0,
    /* EXTI3 */ 0,
    /* EXTI4 */ 0,
    /* DMA1_Stream0 */ 0,
    /* DMA1_Stream1 */ 0,
    /* DMA1_Stream2 */ 0,
    /* DMA1_Stream3 */ 0,
    /* DMA1_Stream4 */ 0,
    /* DMA1_Stream5 */ 0,
    /* DMA1_Stream6 */ 0,
    /* ADC */ 0,
    /* CAN1_TX */ 0,
    /* CAN1_RX0 */ 0,
    /* CAN1_RX1 */ 0,
    /* CAN1_SCE */ 0,
    /* EXTI9_5 */ 0,
    /* TIM1_BRK_TIM9 */ 0,
    /* TIM1_UP_TIM10 */ 0,
    /* TIM1_TRG_COM_TIM11 */ 0,
    /* TIM1_CC */ 0,
    /* TIM2 */ 0,
    /* TIM3 */ 0,
    /* TIM4 */ 0,
    /* I2C1_EV */ 0,
    /* I2C1_ER */ 0,
    /* I2C2_EV */ 0,
    /* I2C2_ER */ 0,
    /* SPI1 */ 0,
    /* SPI2 */ 0,
    /* USART1 */ 0,
    /* USART2 */ 0,
    /* USART3 */ 0,
    /* EXTI15_10 */ exti15_10_handler
};
