# mret uses mepc for return address

m 8000 = 30200073  # mret
csr 341 = c000 # mepc

pc = 8000
.

pc # expect c000
