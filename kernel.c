typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef uint32_t size_t;

extern char __bss[], __bss_end[], __stack_top[];

void *memset(void *buf, char c, size_t n) {
    uint8_t *p = (uint8_t *) buf;
    while (n--)
        *p++ = c;
    return buf;
}

void kernel_main(void) {
    memset(__bss, 0, (size_t) __bss_end - (size_t) __bss);

    for (;;);
}
__attribute__((section(".text.boot")))
__attribute__((naked))
void boot(void) {
    __asm__ volatile(
        "mv sp, %[stack_top]\n" //set stack* to top of stack
        "j kernel_main\n"      // jump to kernel_main fn
        :
        : [stack_top] "r" (__stack_top) // pass stack top addr
    );
}
