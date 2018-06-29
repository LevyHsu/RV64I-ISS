# Misaligned address during instruction fetch

csr 305 = 4000  # mtvec, direct mode
x2 = 0

m 2000 = 00100113  # addi x2, x0, 1

pc = 2001
.

pc       # expect 4000
csr 342  # mcause, expect 0000000000000000 (instruction address misaligned)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200001800
csr 343  # mtval, expect 0000000000002001

x2       # expect 0

csr 342 = 0  # reset mcause
csr 341 = 0  # reset mepc
csr 300 = 0  # reset mstatus
csr 343 = 0  # reset mtval

pc = 2002
.

pc       # expect 4000
csr 342  # mcause, expect 0000000000000000 (instruction address misaligned)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200001800
csr 343  # mtval, expect 0000000000002002

x2       # expect 0

csr 342 = 0  # reset mcause
csr 341 = 0  # reset mepc
csr 300 = 0  # reset mstatus
csr 343 = 0  # reset mtval

pc = 2003
.

pc       # expect 4000
csr 342  # mcause, expect 0000000000000000 (instruction address misaligned)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200001800
csr 343  # mtval, expect 0000000000002003

x2       # expect 0

csr 342 = 2  # reset mcause to non-zero
csr 341 = 0  # reset mepc
csr 300 = 0  # reset mstatus
csr 343 = 0  # reset mtval

pc = 2000
.

pc       # expect 2004
csr 342  # mcause, expect 0000000000000002
csr 341  # mepc, expect 0000000000000000
csr 300  # mstatus, expect 0000000200000000
csr 343  # mtval, expect 0000000000000000

x2       # expect 1

