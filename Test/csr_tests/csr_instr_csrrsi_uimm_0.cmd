# Read/set immediate a read-only CSR using 0 as uimm
# csr rs1 110 rd 1110011 CSRRSI

m 0 = F1306173  # csrrsi x2, 0x00, mimpid

pc = 0
.

csr F13
x2

