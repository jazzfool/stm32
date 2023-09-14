#ifndef HAL2_GPIO_H
#define HAL2_GPIO_H

#include "util.h"
#include <stddef.h>
#include <stdint.h>

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

#define GPIO(_BANK) ((struct gpio*)(0x40020000 + 0x400 * (size_t)(_BANK)))

enum {
    GPIO_MODER_INPUT,
    GPIO_MODER_OUTPUT,
    GPIO_MODER_AF,
    GPIO_MODER_ANALOG
};

static inline void gpio_set_mode(uint16_t pin, uint8_t mode)
{
    struct gpio* gpio = GPIO(PINBANK(pin));
    int n = PINNO(pin);
    gpio->MODER &= ~(0b11u << (n * 2));
    gpio->MODER |= (mode & 0b11u) << (n * 2);
}

static inline void gpio_set_af(uint16_t pin, uint8_t af)
{
    struct gpio* gpio = GPIO(PINBANK(pin));
    int n = PINNO(pin);
    gpio->AFR[n >> 3] &= ~(15ul << ((n & 7) * 4));
    gpio->AFR[n >> 3] |= ((uint32_t)af) << ((n & 7) * 4);
}

static inline void gpio_write(uint16_t pin, uint8_t bit)
{
    struct gpio* gpio = GPIO(PINBANK(pin));
    gpio->BSRR = (1u << PINNO(pin)) << (bit ? 0 : 16);
}

static inline uint8_t gpio_read(uint16_t pin)
{
    struct gpio* gpio = GPIO(PINBANK(pin));
    return (gpio->IDR & BIT(PINNO(pin))) ? 1 : 0;
}

static inline uint8_t gpio_read_odr(uint16_t pin)
{
    struct gpio* gpio = GPIO(PINBANK(pin));
    return (gpio->ODR & BIT(PINNO(pin))) ? 1 : 0;
}

#endif
