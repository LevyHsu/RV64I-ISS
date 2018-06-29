# ebreak trap transfers to mtvec address, ignores mode field

m 1000 = 00100073  # ebreak

csr 305 = 2000  # mtvec, direct mode

pc = 1000
.
pc  # expect 2000

csr 305 = 2001  # mtvec, vectored mode

pc = 1000
.
pc  # expect 2000
