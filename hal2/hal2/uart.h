#ifndef HAL2_usart_H
#define HAL2_usart_H

#include <stdint.h>

struct usart {
    volatile uint32_t
        CR1,
        CR2,
        CR3,
        BRR,
        GTPR,
        RTOR,
        RQR,
        ISR,
        ICR,
        RDR,
        TDR;
};

#define USART3 ((struct usart*)(0x40004800))

static inline void usart_set_usart_enabled(struct usart* usart, uint8_t enabled)
{
    usart->CR1 &= ~1u;
    usart->CR1 |= (enabled & 0b1u);
}

static inline void usart_set_rx_enabled(struct usart* usart, uint8_t enabled)
{
    usart->CR1 &= ~(1u << 2);
    usart->CR1 |= ((enabled & 0b1u) << 2);
}

static inline void usart_set_tx_enabled(struct usart* usart, uint8_t enabled)
{
    usart->CR1 &= ~(1u << 3);
    usart->CR1 |= ((enabled & 0b1u) << 3);
}

static inline void usart_set_word_length(struct usart* usart, uint8_t word_length)
{
    uint8_t m0 = 0, m1 = 0; /* default 00 = 8 bits */
    if (word_length == 7) {
        m0 = 1, m1 = 1;
    } else if (word_length == 9) {
        m0 = 1, m1 = 0;
    }
    usart->CR1 &= ~(1u << 12);
    usart->CR1 &= ~(1u << 28);
    usart->CR1 |= ((m0 & 0b1u) << 12);
    usart->CR1 |= ((m1 & 0b1u) << 28);
}

static inline void usart_set_baud_rate(struct usart* usart, uint32_t baud)
{
    usart->BRR = 16000000 / baud;
}

static inline uint8_t usart_read_rxne(struct usart* usart)
{
    return usart->ISR & (1 << 5);
}

static inline uint8_t usart_read_txe(struct usart* usart)
{
    return usart->ISR & (1 << 7);
}

static inline uint8_t usart_read_byte(struct usart* usart)
{
    return (uint8_t)(usart->RDR & 0xFF);
}

static inline void usart_write_byte(struct usart* usart, uint8_t byte)
{
    usart->TDR = byte;
}

#endif
