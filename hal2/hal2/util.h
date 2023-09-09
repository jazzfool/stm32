#ifndef HAL2_UTIL_H
#define HAL2_UTIL_H

#define BIT(_N) (1ul << (_N))
#define NBITMASK(_N) ((1ul << (_N)) - 1ul)
#define PIN(_BANKCHAR, _PINNO) ((((_BANKCHAR) - 'A') << 8) | (_PINNO))
#define PINBANK(_PIN) (_PIN >> 8)
#define PINNO(_PIN) (_PIN & 255)

#endif
