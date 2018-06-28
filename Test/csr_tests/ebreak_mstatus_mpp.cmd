# ebreak trap pushes privilege level stack correctly

m 1000 = 00100073  # ebreak
csr 305 = 2000  # mtvec, direct mode

pc = 1000
.

csr 300  # mstatus, expect 0000000200001800
prv  # expect 3 (machine)

pc = 1000
.

csr 300  # mstatus, expect 0000000200001800
prv  # expect 3 (machine)

prv = 0

pc = 1000
.

csr 300  # mstatus, expect 0000000200000000
prv  # expect 3 (machine)

prv = 0

pc = 1000
.

csr 300  # mstatus, expect 0000000200000000
prv  # expect 3 (machine)

