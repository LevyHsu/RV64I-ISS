# Misaligned address during ld load instruction

csr 305 = 4000  # mtvec, direct mode

m 2000 = 0000B103  # ld x2, 0(x1)
x2 = 0
m 1000 = 7766554433221100
m 1008 = FFEEDDCCBBAA9988

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

pc       # expect 4000
csr 342  # mcause, expect 0000000000000004 (load address misaligned)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200001800
csr 343  # mtval, expect 0000000000001002
x2       # expect 0

csr 342 = 0  # reset mcause
csr 341 = 0  # reset mepc
csr 300 = 0  # reset mstatus
csr 343 = 0  # reset mtval

################

x1 = 1003
pc = 2000
.

pc       # expect 4000
csr 342  # mcause, expect 0000000000000004 (load address misaligned)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200001800
csr 343  # mtval, expect 0000000000001003
x2       # expect 0

csr 342 = 0  # reset mcause
csr 341 = 0  # reset mepc
csr 300 = 0  # reset mstatus
csr 343 = 0  # reset mtval

################

x1 = 1004
pc = 2000
.

pc       # expect 4000
csr 342  # mcause, expect 0000000000000004 (load address misaligned)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200001800
csr 343  # mtval, expect 0000000000001004
x2       # expect 0

csr 342 = 0  # reset mcause
csr 341 = 0  # reset mepc
csr 300 = 0  # reset mstatus
csr 343 = 0  # reset mtval

################

x1 = 1005
pc = 2000
.

pc       # expect 4000
csr 342  # mcause, expect 0000000000000004 (load address misaligned)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200001800
csr 343  # mtval, expect 0000000000001005
x2       # expect 0

csr 342 = 0  # reset mcause
csr 341 = 0  # reset mepc
csr 300 = 0  # reset mstatus
csr 343 = 0  # reset mtval

################

x1 = 1006
pc = 2000
.

pc       # expect 4000
csr 342  # mcause, expect 0000000000000004 (load address misaligned)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200001800
csr 343  # mtval, expect 0000000000001006
x2       # expect 0

csr 342 = 0  # reset mcause
csr 341 = 0  # reset mepc
csr 300 = 0  # reset mstatus
csr 343 = 0  # reset mtval

################

x1 = 1007
pc = 2000
.

pc       # expect 4000
csr 342  # mcause, expect 0000000000000004 (load address misaligned)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200001800
csr 343  # mtval, expect 0000000000001007
x2       # expect 0

csr 342 = 0  # reset mcause
csr 341 = 0  # reset mepc
csr 300 = 0  # reset mstatus
csr 343 = 0  # reset mtval

################

x1 = 1008
pc = 2000
.

pc       # expect 2004
csr 342  # mcause, expect 0000000000000000
csr 341  # mepc, expect 0000000000000000
csr 300  # mstatus, expect 0000000200000000
csr 343  # mtval, expect 0000000000000000

x2       # expect FFEEDDCCBBAA9988

