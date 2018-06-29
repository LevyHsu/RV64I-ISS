# Misaligned address during sh store instruction

csr 305 = 4000  # mtvec, direct mode

m 2000 = 00209023  # sh x2, 0(x1)
x2 = FEDCBA9876543210
m 1000 = 7766554433221100

################

x1 = 1001
pc = 2000
.

pc       # expect 4000
csr 342  # mcause, expect 0000000000000006 (store address misaligned)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200001800
csr 343  # mtval, expect 0000000000001001
m 1000   # expect 7766554433221100

csr 342 = 0  # reset mcause
csr 341 = 0  # reset mepc
csr 300 = 0  # reset mstatus
csr 343 = 0  # reset mtval

################

x1 = 1002
pc = 2000
.

pc       # expect 2004
csr 342  # mcause, expect 0000000000000000
csr 341  # mepc, expect 0000000000000000
csr 300  # mstatus, expect 0000000200000000
csr 343  # mtval, expect 0000000000000000

m 1000   # expect 7766554432101100
