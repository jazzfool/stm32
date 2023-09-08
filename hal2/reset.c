int main(void);

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
    _estack, _reset_handler
};
