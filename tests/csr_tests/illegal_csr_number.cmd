# Illegal instruction trap on undefined csr number

csr 305 = 4000  # mtvec, direct mode

m 2000 = 30209173  # csrrw x2, x1, medeleg
x1 = 123456789abcdef0
x2 = 0202020202020202
pc = 2000
.

pc       # expect 4000
csr 342  # mcause, expect 0000000000000002 (illegal instruction)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200001800
csr 343  # mtval, expect 0000000030209173

x2       # expect 0202020202020202
