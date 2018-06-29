# User software interrupt (cause 0) in machine mode, vectored

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

# All enabled; USI, MSI, UTI, MTI, UEI, MEI pending

csr 300 = 0000000200000008  # mpie = 0, mie = 1
csr 304 = 0000000000000999  # set mie.{usie, msie, utie, mtie, ueie, meie}
csr 344 = 0000000000000999  # set mip.{usip, msip, utip, mtip, ueip, meip}
csr 342 = 0000000000000000  # mcause
csr 341 = 0000000000000000  # mepc
prv = 3

pc = 1000
.

prv      # expect 3
pc       # expect 2030 (mei has highest priority of pending interrupts)
csr 300  # expect mstatus = 0000000200001880
csr 342  # expect mcause = 800000000000000B
csr 341  # expect mepc = 0000000000001000

# All enabled; USI, MSI, UTI, MTI, UEI pending

csr 300 = 0000000200000008  # mpie = 0, mie = 1
csr 304 = 0000000000000999  # set mie.{usie, msie, utie, mtie, ueie, meie}
csr 344 = 0000000000000199  # set mip.{usip, msip, utip, mtip, ueip}
csr 342 = 0000000000000000  # mcause
csr 341 = 0000000000000000  # mepc
prv = 3

pc = 1000
.

prv      # expect 3
pc       # expect 2010 (msi has highest priority of pending interrupts)
csr 300  # expect mstatus = 0000000200001880
csr 342  # expect mcause = 8000000000000003
csr 341  # expect mepc = 0000000000001000

# All enabled; USI, UTI, MTI, UEI pending

csr 300 = 0000000200000008  # mpie = 0, mie = 1
csr 304 = 0000000000000999  # set mie.{usie, msie, utie, mtie, ueie, meie}
csr 344 = 0000000000000191  # set mip.{usip, utip, mtip, ueip}
csr 342 = 0000000000000000  # mcause
csr 341 = 0000000000000000  # mepc
prv = 3

pc = 1000
.

prv      # expect 3
pc       # expect 2020 (mti has highest priority of pending interrupts)
csr 300  # expect mstatus = 0000000200001880
csr 342  # expect mcause = 8000000000000007
csr 341  # expect mepc = 0000000000001000

# All enabled; USI, UTI, UEI pending

csr 300 = 0000000200000008  # mpie = 0, mie = 1
csr 304 = 0000000000000999  # set mie.{usie, msie, utie, mtie, ueie, meie}
csr 344 = 0000000000000111  # set mip.{usip, utip, ueip}
csr 342 = 0000000000000000  # mcause
csr 341 = 0000000000000000  # mepc
prv = 3

pc = 1000
.

prv      # expect 3
pc       # expect 2024 (uei has highest priority of pending interrupts)
csr 300  # expect mstatus = 0000000200001880
csr 342  # expect mcause = 8000000000000008
csr 341  # expect mepc = 0000000000001000

# All enabled; USI, UTI pending

csr 300 = 0000000200000008  # mpie = 0, mie = 1
csr 304 = 0000000000000999  # set mie.{usie, msie, utie, mtie, ueie, meie}
csr 344 = 0000000000000011  # set mip.{usip, utip}
csr 342 = 0000000000000000  # mcause
csr 341 = 0000000000000000  # mepc
prv = 3

pc = 1000
.

prv      # expect 3
pc       # expect 2004 (usi has highest priority of pending interrupts)
csr 300  # expect mstatus = 0000000200001880
csr 342  # expect mcause = 8000000000000000
csr 341  # expect mepc = 0000000000001000

# All enabled; UTI pending

csr 300 = 0000000200000008  # mpie = 0, mie = 1
csr 304 = 0000000000000999  # set mie.{usie, msie, utie, mtie, ueie, meie}
csr 344 = 0000000000000010  # set mip.{utip}
csr 342 = 0000000000000000  # mcause
csr 341 = 0000000000000000  # mepc
prv = 3

pc = 1000
.

prv      # expect 3
pc       # expect 2014 (uti has highest priority of pending interrupts)
csr 300  # expect mstatus = 0000000200001880
csr 342  # expect mcause = 8000000000000004
csr 341  # expect mepc = 0000000000001000

