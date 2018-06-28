# mip.ueip read only

m 0 = 3440B1733440A173  # csrrs x2, x1, mip; csrrc x2, x1, mip

csr 344  # expect initial mip = 0000000000000000

x1 = 0000000000000100  # mask for ueip
pc = 0
.

csr 344  # expect mip = 0000000000000100
x2       # expect 0000000000000000

pc = 4
.

csr 344  # expect mip = 0000000000000000
x2       # expect 0000000000000100

