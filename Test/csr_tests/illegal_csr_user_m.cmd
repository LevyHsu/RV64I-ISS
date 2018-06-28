# Illegal instruction trap on machine csr access in user mode

prv = 0  # User mode

csr 305 = 4000  # mtvec, direct mode

m 2000 = 34009173  # csrrw x2, x1, mscratch
csr 340 = ABABABABABABABAB
x1 = 123456789abcdef0
x2 = 0202020202020202
pc = 2000
.

pc       # expect 4000
csr 342  # mcause, expect 0000000000000002 (illegal instruction)
csr 341  # mepc, expect 0000000000002000
csr 300  # mstatus, expect 0000000200000000
csr 343  # mtval, expect 0000000034009173

csr 340  # expect ABABABABABABABAB
x2       # expect 0202020202020202
