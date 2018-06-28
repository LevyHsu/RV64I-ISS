# Read/write immediate a writable CSR
# csr uimm 101 rd 1110011 CSRRWI

m 0 = 340AD173  # csrrwi x2, 0x15, mscratch
pc = 0
.

csr 340
x2

m 0 = 34055173  # csrrwi x2, 0x0A, mscratch
pc = 0
.

csr 340
x2

m 0 = 340E5173  # csrrwi x0, 0x1C, mscratch
pc = 0
.

csr 340
x0
