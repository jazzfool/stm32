#ifdef HAL2_NOHANDLERS_H
#error include once
#endif

#define HAL2_NOHANDLERS_H

#ifndef SYSTICK_HANDLER
void systick_handler(void)
{
}
#endif

#ifndef EXTI15_10_HANDLER
void exti15_10_handler(void)
{
}
#endif
