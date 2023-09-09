#ifndef HAL2_EXTI_H
#define HAL2_EXTI_H

#include "util.h"
#include <stdint.h>

struct exti {
    volatile uint32_t
        IMR,
        EMR,
        RTSR,
        FTSR,
        SWIER,
        PR;
};

#define EXTI ((struct exti*)(0x40013C00))

static inline void exti_set_imr(uint8_t line, uint8_t bit)
{
    EXTI->IMR &= ~(BIT(line));
    EXTI->IMR |= ((bit & 0b1u) << line);
}

static inline void exti_set_rtsr(uint8_t line, uint8_t bit)
{
    EXTI->RTSR &= ~(BIT(line));
    EXTI->RTSR |= ((bit & 0b1u) << line);
}

static inline void exti_set_ftsr(uint8_t line, uint8_t bit)
{
    EXTI->FTSR &= ~(BIT(line));
    EXTI->FTSR |= ((bit & 0b1u) << line);
}

static inline void exti_clear_pr(uint8_t line)
{
    EXTI->PR &= ~(BIT(line));
}

#endif
