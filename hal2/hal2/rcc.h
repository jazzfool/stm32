#ifndef HAL2_RCC_H
#define HAL2_RCC_H

#include <inttypes.h>

struct rcc {
    volatile uint32_t
        CR,
        PLLCFGR,
        CFGR,
        CIR,
        AHB1RSTR,
        AHB2RSTR,
        AHB3RSTR,
        _RSV01, /* reserved */
        APB1RSTR,
        APB2RSTR,
        _RSV02, /* reserved */
        _RSV03, /* reserved */
        AHB1ENR,
        AHB2ENR,
        AHB3ENR,
        _RSV04, /* reserved */
        APB1ENR,
        APB2ENR,
        _RSV05, /* reserved */
        _RSV06, /* reserved */
        AHB1LPENR,
        AHB2LPENR,
        AHB3LPENR,
        _RSV07, /* reserved */
        APB1LPENR,
        APB2LPENR,
        _RSV08, /* reserved */
        _RSV09, /* reserved */
        BDCR,
        CSR,
        _RSV10, /* reserved */
        _RSV11, /* reserved */
        SSCGR,
        PLLI2SCFGR,
        PLLSAICFGR,
        DCKCFGR1,
        DCKCFGR2;
};

#define RCC ((struct rcc*)(0x40023800))

#endif
