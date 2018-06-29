# Read/clear immediate a writable CSR
# csr uimm 111 rd 1110011 CSRRCI

csr 340 = FEFEFEFE7F7F7F7F

m 0 = 3402f173  # csrrci x2, 0x05, mscratch
pc = 0
.

csr 340
x2

m 0 = 340af173  # csrrci x2, 0x15, mscratch
pc = 0
.

csr 340
x2

m 0 = 34007173  # csrrci x2, 0x00, mscratch
pc = 0
.

csr 340
x2

m 0 = 34017073  # csrrci x0, 0x02, mscratch
pc = 0
.

csr 340
x0
