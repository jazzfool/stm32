#ifndef HAL2_GPIO_H
#define HAL2_GPIO_H

#include <inttypes.h>

struct gpio {
    volatile uint32_t
        MODER,
        OTYPER,
        OSPEEDR,
        PUPDR,
        IDR,
        ODR,
        BSRR,
        LCKR,
        AFR[2];
};

#define GPIO(_BANK) ((struct gpio*)(0x40020000 + 0x400 * (uint64_t)(_BANK)))

enum {
    GPIO_MODER_INPUT,
    GPIO_MODER_OUTPUT,
    GPIO_MODER_AF,
    GPIO_MODER_ANALOG
};

#define BIT(_N) (1ul << (_N))
#define PIN(_BANKCHAR, _PINNO) ((((_BANKCHAR) - 'A') << 8) | (_PINNO))
#define PINBANK(_PIN) (_PIN >> 8)
#define PINNO(_PIN) (_PIN & 255)

static inline void gpio_set_mode(uint16_t pin, uint8_t mode) {
    struct gpio* gpio = GPIO(PINBANK(pin));
    int n = PINNO(pin);
    gpio->MODER &= ~(0b11 << (n * 2));
    gpio->MODER |= (mode & 0b11) << (n * 2);
}

static inline void gpio_write(uint16_t pin, uint8_t bit) {
    struct gpio* gpio = GPIO(PINBANK(pin));
    gpio->BSRR = (1u << PINNO(pin)) << (bit ? 0 : 16);
}

#endif
