# ebreak trap pushes interrupt enable stack correctly

m 1000 = 00100073  # ebreak
csr 305 = 2000  # mtvec, direct mode

# Machine mode

csr 300 = 0000000200000000  # mpie = 0, mie = 0

pc = 1000
.

csr 300  # mstatus, expect 0000000200001800

csr 300 = 0000000200000008  # mpie = 0, mie = 1

pc = 1000
.

csr 300  # mstatus, expect 0000000200001880

csr 300 = 0000000200000088  # mpie = 1, mie = 1

pc = 1000
.

csr 300  # mstatus, expect 0000000200001880

# User mode

csr 300 = 0000000200000000  # mpie = 0, mie = 0
prv = 0

pc = 1000
.

csr 300  # mstatus, expect 0000000200000000

csr 300 = 0000000200000008  # mpie = 0, mie = 1
prv = 0

pc = 1000
.

csr 300  # mstatus, expect 0000000200000080

csr 300 = 0000000200000088  # mpie = 1, mie = 1
prv = 0

pc = 1000
.

csr 300  # mstatus, expect 0000000200000080
