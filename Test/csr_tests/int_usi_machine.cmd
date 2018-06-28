# User software interrupt (cause 0) in machine mode

m 1000 = 0000001300000013  # nop; nop
m 2000 = 0000001300000013  # nop; nop
m 2008 = 0000001300000013  # nop; nop
m 2010 = 0000001300000013  # nop; nop
m 2018 = 0000001300000013  # nop; nop
m 2020 = 0000001300000013  # nop; nop
m 2028 = 0000001300000013  # nop; nop
m 2030 = 0000001300000013  # nop; nop
m 2038 = 0000001300000013  # nop; nop

csr 305 = 2000  # mtvec, direct mode

# USI disabled, globally disabled

csr 300 = 0000000200000000  # mpie = 0, mie = 0
csr 304 = 0000000000000000  # mie.usie = 0
csr 344 = 0000000000000001  # mip.usip = 1
csr 342 = 0000000000000000  # mcause
csr 341 = 0000000000000000  # mepc
prv = 3

pc = 1000
.

prv      # expect 3
pc       # expect 1004
csr 300  # expect mstatus = 0000000200000000
csr 342  # expect mcause = 0000000000000000
csr 341  # expect mepc = 0000000000000000

# non-USI enabled, globally disabled

csr 300 = 0000000200000000  # mpie = 0, mie = 0
csr 304 = 0000000000000998  # mie.usie = 0, others enabled
csr 344 = 0000000000000001  # mip.usip = 1
csr 342 = 0000000000000000  # mcause
csr 341 = 0000000000000000  # mepc
prv = 3

pc = 1000
.

prv      # expect 3
pc       # expect 1004
csr 300  # expect mstatus = 0000000200000000
csr 342  # expect mcause = 0000000000000000
csr 341  # expect mepc = 0000000000000000

# USI enabled, globally disabled

csr 300 = 0000000200000000  # mpie = 0, mie = 0
csr 304 = 0000000000000001  # mie.usie = 1
csr 344 = 0000000000000001  # mip.usip = 1
csr 342 = 0000000000000000  # mcause
csr 341 = 0000000000000000  # mepc
prv = 3

pc = 1000
.

prv      # expect 3
pc       # expect 1004
csr 300  # expect mstatus = 0000000200000000
csr 342  # expect mcause = 0000000000000000
csr 341  # expect mepc = 0000000000000000

# USI enabled, globally enabled

csr 300 = 0000000200000008  # mpie = 0, mie = 1
csr 304 = 0000000000000001  # mie.usie = 1
csr 344 = 0000000000000001  # mip.usip = 1
csr 342 = 0000000000000000  # mcause
csr 341 = 0000000000000000  # mepc
prv = 3

pc = 1000
.

prv      # expect 3
pc       # expect 2004
csr 300  # expect mstatus = 0000000200001880
csr 342  # expect mcause = 8000000000000000
csr 341  # expect mepc = 0000000000001000

