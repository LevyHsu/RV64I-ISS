# ebreak trap sets mepc correctly

m 1000 = 00100073  # ebreak
csr 305 = 2000  # mtvec, direct mode

pc = 1000
.

csr 341  # mepc, expect 0000000000001000
