# Read/set a writable CSR
# csr rs1 010 rd 1110011 CSRRS

m 0 = 3400A173  # csrrs x2, x1, mscratch

csr 340 = 0101010180808080
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

m 0 = 3400A073  # csrrs x0, x1, mscratch

x1 = 4040000020200000
pc = 0
.

csr 340
x0
