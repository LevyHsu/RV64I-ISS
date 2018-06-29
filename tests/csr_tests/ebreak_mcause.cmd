# ebreak trap sets mcause correctly

m 1000 = 00100073  # ebreak
csr 305 = 2000  # mtvec, direct mode

pc = 1000
.

csr 342  # mcause, expect 0000000000000003
