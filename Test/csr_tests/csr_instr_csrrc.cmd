# Read/clear a writable CSR
# csr rs1 011 rd 1110011 CSRRC

m 0 = 3400B173  # csrrc x2, x1, mscratch

csr 340 = FEFEFEFE7F7F7F7F
x1 = 8080808040404040
pc = 0
.

csr 340
x2

x1 = A0A0A0A010101010
pc = 0
.

csr 340
x2

x1 = 0
pc = 0
.

csr 340
x2

m 0 = 3400B073  # csrrc x0, x1, mscratch

x1 = 4040000020200000
pc = 0
.

csr 340
x0
