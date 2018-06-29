typedef enum {PRV_USER = 0,
              PRV_SUPERVISOR = 1,
              PRV_MACHINE = 3} prv_t;

extern prv_t set_prv(prv_t prv);

int main (void) {
    prv_t prv;
    prv = set_prv(PRV_MACHINE);
    if (prv != PRV_MACHINE) return 1;  // expect PRV_MACHINE
    prv = set_prv(PRV_USER);
    if (prv != PRV_MACHINE) return 2;  // expect PRV_MACHINE
    prv = set_prv(PRV_USER);
    if (prv != PRV_USER) return 3;     // expect PRV_USER
    prv = set_prv(PRV_MACHINE);
    if (prv != PRV_USER) return 4;     // expect PRV_USER
    prv = set_prv(PRV_MACHINE);
    if (prv != PRV_MACHINE) return 5;  // expect PRV_MACHINE
    return 0;
}
