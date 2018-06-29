# Misaligned address during lh/lhu load instruction

csr 305 = 4000  # mtvec, direct mode

m 2000 = 00009103  # lh x2, 0(x1)
x2 = 0
m 1000 = FFEEDDCCBBAA9988

################

x1 = 1001
pc = 2000
.

pc       # expect 4000
csr 342  # mcause, expect 0000000000000004 (load address misaligned)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200001800
csr 343  # mtval, expect 0000000000001001
x2       # expect 0

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

x2       # expect FFFFFFFFFFFFBBAA

csr 342 = 0  # reset mcause
csr 341 = 0  # reset mepc
csr 300 = 0  # reset mstatus
csr 343 = 0  # reset mtval

################

m 2000 = 0000D103  # lhu x2, 0(x1)
x2 = 0

x1 = 1001
pc = 2000
.

pc       # expect 4000
csr 342  # mcause, expect 0000000000000004 (load address misaligned)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200001800
csr 343  # mtval, expect 0000000000001001
x2       # expect 0

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

x2       # expect 000000000000BBAA
