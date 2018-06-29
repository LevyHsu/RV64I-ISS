# Set unused bits of a writable CSR

# mstatus: only mie, mpie, mpp implemented
csr 300 = fffffffdffffffff
csr 300 # expect 0000000200001888

# misa: all bits fixed
csr 301 = 7fffffffffeffeff
csr 301 # expect 8000000000100100

# mie: only usie, msie, utie, mtie, ueie, meie implemented
csr 304 = ffffffffffffffff
csr 304 # expect 0000000000000999

# mtvec: bit 1 fixed at 0, if vectored, bits 7:2 also fixed at 0

csr 305 = fffffffffffffffe  # Direct mode
csr 305 # expect fffffffffffffffc
csr 305 = 0000000000000000
csr 305 # expect 0000000000000000
csr 305 = ffffffffffffffff  # Vectored mode
csr 305 # expect ffffffffffffff01

# mscratch: all bits writable

csr 340 = ffffffffffffffff
csr 340 # expect ffffffffffffffff

# mepc: bit 1:0 fixed at 0

csr 341 = ffffffffffffffff
csr 341 # expect fffffffffffffffc

# mcause: only Interrupt bit and 4-bit cause

csr 342 = ffffffffffffffff
csr 342 # expect 800000000000000f

# mtval: all bits writable

csr 343 = ffffffffffffffff
csr 343 # expect ffffffffffffffff

# mip: only usip, msip, utip, mtip, ueip, meip implemented
csr 344 = ffffffffffffffff
csr 344 # expect 0000000000000999
