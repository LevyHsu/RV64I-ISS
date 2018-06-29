# mret pops privilege level stack correctly

m 8000 = 30200073  # mret
csr 341 = c000 # mepc

prv = 3 # machine mode
csr 300 = 0000000200001800 # mpp = 3 (machine)

pc = 8000
.
prv # expect 3 (machine)
csr 300 # expect 0000000200000080, mpp = 0 (user)

prv = 3 # machine mode
csr 300 = 0000000200000000 # mpp = 0 (user)

pc = 8000
.
prv # expect 0 (user)
csr 300 # expect 0000000200000080, mpp = 0 (user)

