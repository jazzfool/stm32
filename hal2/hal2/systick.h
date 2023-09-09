#ifndef HAL2_SYSTICK_H
#define HAL2_SYSTICK_H

#include "util.h"
#include <stdint.h>

struct systick {
    volatile uint32_t
        CSR,
        RVR,
        CVR,
        CALIB;
};

#define SYSTICK ((struct systick*)(0xE000E010ul))

static inline void systick_set_enable(uint8_t enable)
{
    SYSTICK->CSR &= ~(BIT(0));
    SYSTICK->CSR |= (enable & 0b1u);
}

static inline void systick_set_tickint(uint8_t tickint)
{
    SYSTICK->CSR &= ~(BIT(1));
    SYSTICK->CSR |= ((tickint & 0b1) << 1);
}

static inline void systick_set_clksource(uint8_t clksource)
{
    SYSTICK->CSR &= ~(BIT(2));
    SYSTICK->CSR |= ((clksource & 0b1u) << 2);
}

static inline void systick_set_reload_value(uint32_t reload)
{
    SYSTICK->RVR &= 0;
    SYSTICK->RVR |= reload & NBITMASK(23);
}

static inline uint32_t systick_read_calib_tenms()
{
    return SYSTICK->CALIB & NBITMASK(23);
}

#endif
