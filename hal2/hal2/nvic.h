#ifndef HAL2_NVIC_H
#define HAL2_NVIC_H

#include "util.h"
#include <stdint.h>

struct nvic {
    volatile uint32_t
        ISER[8],
        _RSV01[24],
        ICER[8],
        _RSV02[24],
        ISPR[8],
        _RSV03[24],
        ICPR[8],
        _RSV04[24],
        IABR[8],
        _RSV05[56];
    volatile uint8_t IPR[240];
    volatile uint32_t
        _RSV06[644],
        STIR;
};

#define NVIC ((struct nvic*)(0xE000E100))

static inline void nvic_set_enable_interrupt(uint32_t lane)
{
    const uint32_t i = lane / 32;
    const uint32_t n = lane % 32;
    NVIC->ISER[i] |= (1 << n);
}

static inline void nvic_clear_enable_interrupt(uint32_t lane)
{
    const uint32_t i = lane / 32;
    const uint32_t n = lane % 32;
    NVIC->ICER[i] |= (1 << n);
}

#endif
