# Machine software interrupt (cause 3) in machine mode, vectored

m 1000 = 0000001300000013  # nop; nop
m 2000 = 0000001300000013  # nop; nop
m 2008 = 0000001300000013  # nop; nop
m 2010 = 0000001300000013  # nop; nop
m 2018 = 0000001300000013  # nop; nop
m 2020 = 0000001300000013  # nop; nop
m 2028 = 0000001300000013  # nop; nop
m 2030 = 0000001300000013  # nop; nop
m 2038 = 0000001300000013  # nop; nop

csr 305 = 2001  # mtvec, vectored mode

# MSI enabled, globally enabled

csr 300 = 0000000200000008  # mpie = 0, mie = 1
csr 304 = 0000000000000008  # mie.msie = 1
csr 344 = 0000000000000008  # mip.msip = 1
csr 342 = 0000000000000000  # mcause
csr 341 = 0000000000000000  # mepc
prv = 3

pc = 1000
.

prv      # expect 3
pc       # expect 2010
csr 300  # expect mstatus = 0000000200001880
csr 342  # expect mcause = 8000000000000003
csr 341  # expect mepc = 0000000000001000

