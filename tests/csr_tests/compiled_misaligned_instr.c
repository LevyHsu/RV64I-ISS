#include <stdint.h>

int f0(void) {
    return -1;
}

int f1(void) {
    return 1;
}

int main (void) {
    int i;
    int (*p)(void);
    p = (int (*)(void))((char*)(&f1) + 2);
    i = (*p)();
    return i;
}
