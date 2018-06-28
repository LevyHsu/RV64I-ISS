# mip.mtip read only

m 0 = 3440A173  # csrrs x2, x1, mip

csr 344  # expect initial mip = 0000000000000000

x1 = 0000000000000080  # mask for mtip
pc = 0
.

csr 344  # expect mip = 0000000000000000
x2       # expect 0000000000000000

