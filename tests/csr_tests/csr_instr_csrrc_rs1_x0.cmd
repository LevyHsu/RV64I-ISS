# Read/clear a read-only CSR using x0 as rs1
# csr rs1 011 rd 1110011 CSRRC

m 0 = F1303173  # csrrs x2, x0, mimpid

pc = 0
.

csr F13
x2

