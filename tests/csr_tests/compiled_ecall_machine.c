#include <stdbool.h>

extern bool set_ie(bool ie);

int main (void) {
    bool ie;
    ie = set_ie(false);
    if (ie) return 1;  // expect false
    ie = set_ie(true);
    if (ie) return 2;  // expect false
    ie = set_ie(true);
    if (!ie) return 3;  // expect true
    ie = set_ie(false);
    if (!ie) return 4;  // expect true
    ie = set_ie(false);
    if (ie) return 5;  // expect false
    return 0;
}
