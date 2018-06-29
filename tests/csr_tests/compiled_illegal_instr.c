#include <stdint.h>

int f0(void) {
    return -1;
}

int main (void) {
    uint32_t f_ok[2];
    uint32_t f_illegal;
    f_ok[0] = 0x00100513; // li a0, 1
    f_ok[1] = 0x00008067; // ret
    f_illegal = 0x02c58533; // mul x10, x11, x12
    int i;
    int (*p)(void);
    p = (int (*)(void))(&f_ok);
    if ((*p)() != 1) return 0;
    p = (int (*)(void))(&f_illegal);
    if ((*p)() != -1) return 0;
    return 1;
}
