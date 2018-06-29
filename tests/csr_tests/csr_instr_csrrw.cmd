# Read/write a writable CSR
# csr rs1 001 rd 1110011 CSRRW

m 0 = 34009173  # csrrw x2, x1, mscratch

x1 = 123456789abcdef0
pc = 0
.

csr 340
x2

x1 = 0fedcba987654321
pc = 0
.

csr 340
x2

m 0 = 34009073  # csrrw x0, x1, mscratch

x1 = 81817F7F6C6C2C2C
pc = 0
.

csr 340
x0
