# ecall instruction executed in user mode

prv = 0  # User mode

csr 305 = 4000  # mtvec, direct mode

m 2000 = 00000073  # ecall
pc = 2000
.

pc       # expect 4000
csr 342  # mcause, expect 0000000000000008 (ecall from user mode)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200000000
csr 343  # mtval, expect 0000000000000000
