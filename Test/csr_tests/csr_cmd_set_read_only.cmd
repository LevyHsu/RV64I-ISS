# Set read only CSR gives error

csr f11 = ffffffffffffffff
csr f11 # expect 0000000000000000

csr f12 = ffffffffffffffff
csr f12 # expect 0000000000000000

csr f13 = dfe7fdffffffffff
csr f13 # expect 2018020000000000

csr f14 = ffffffffffffffff
csr f14 # expect 0000000000000000
