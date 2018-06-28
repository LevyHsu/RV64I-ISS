# Illegal instruction trap on write to read only CSR

csr 305 = 4000  # mtvec, direct mode

m 2000 = F130A173  # csrrs x2, x1, mimpid

x1 = 00000000FFFFFFFF
x2 = 0202020202020202
pc = 2000
.

pc       # expect 4000
csr 342  # mcause, expect 0000000000000002 (illegal instruction)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200001800
csr 343  # mtval, expect 00000000F130A173

x2       # expect 0202020202020202

csr 342 = 0  # reset mcause
csr 341 = 0  # reset mepc
csr 300 = 0  # reset mstatus
csr 343 = 0  # reset mtval

x1 = 0
pc = 2000
.

pc       # expect 4000
csr 342  # mcause, expect 0000000000000002 (illegal instruction)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200001800
csr 343  # mtval, expect 00000000F130A173

x2       # expect 0202020202020202
