# Read all defined CSRs

csr f11	  # mvendorid, expect 0000000000000000
csr F12   # marchid, expect 0000000000000000
csr F13   # mimpid, expect 2018020000000000
csr F14   # mhartid, expect 0000000000000000
csr 300   # mstatus, expect 0000000200000000
csr 301   # misa, expect 8000000000100100
csr 304   # mie, expect 0000000000000000
csr 305   # mtvec, expect 0000000000000000
csr 340   # mscratch, expect 0000000000000000
csr 341   # mepc, expect 0000000000000000
csr 342   # mcause, expect 0000000000000000
csr 343   # mtval, expect 0000000000000000
csr 344   # mip, expect 0000000000000000
