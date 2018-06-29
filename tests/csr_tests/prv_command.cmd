# Set and show privilege level

prv   # expect 3 (machine)

prv = 3
prv   # expect 3 (machine)

prv = 0
prv   # expect 0 (user)

prv = 0
prv   # expect 0 (user)

prv = 3
prv   # expect 3 (machine)

