# Read/set immediate a writable CSR
# csr uimm 110 rd 1110011 CSRRSI

csr 340 = 0101010180808080

m 0 = 3402e173  # csrrsi x2, 0x05, mscratch
pc = 0
.

csr 340
x2

m 0 = 340ae173  # csrrsi x2, 0x15, mscratch
pc = 0
.

csr 340
x2

m 0 = 34006173  # csrrsi x2, 0x00, mscratch
pc = 0
.

csr 340
x2

m 0 = 34016073  # csrrsi x0, 0x02, mscratch
pc = 0
.

csr 340
x0
