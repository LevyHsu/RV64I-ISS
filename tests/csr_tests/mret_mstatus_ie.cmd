# mret pops mstatus interrupt stack correctly

m 8000 = 30200073  # mret
csr 341 = c000 # mepc

csr 300 = 0000000200001800 # mpie = 0, mie = 0
pc = 8000
.
csr 300 # expect 0000000200000080, mpie = 1, mie = 0

csr 300 = 0000000200001880 # mpie = 1, mie = 0
pc = 8000
.
csr 300 # expect 0000000200000088, mpie = 1, mie = 1

csr 300 = 0000000200001808 # mpie = 0, mie = 1
pc = 8000
.
csr 300 # expect 0000000200000080, mpie = 1, mie = 0

csr 300 = 0000000200001888 # mpie = 1, mie = 1
pc = 8000
.
csr 300 # expect 0000000200000088, mpie = 1, mie = 1

