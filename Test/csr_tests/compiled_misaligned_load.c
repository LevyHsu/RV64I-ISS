#include <stdint.h>

uint64_t main (void) {
    uint64_t a[2];
    uint64_t b, c;
    uint64_t *p;
    int i;
    a[0] = 0x0706050403020100ULL;
    a[1] = 0x1716151413121110ULL;
    for (i = 1; i <= 7; i++) {
	p = (uint64_t*)((uint8_t*)(&a[0]) + i);
	b = *p;
	c = (a[0] >> (i*8)) | (a[1] << (64 - i*8));
	if (b != c) return 0;
    }
    return 1;
}
