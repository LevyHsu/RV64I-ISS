l "compiled_int_quicksort.hex"
. 10000

csr 344 = 0000000000000001  # mip.usip = 1
.
csr 344 = 0000000000000000  # mip.usip = 0
. 10000
pc
m 10000
m 10008
m 10010

csr 344 = 0000000000000008  # mip.msip = 1
.
csr 344 = 0000000000000000  # mip.msip = 0
. 10000
csr 344 = 0000000000000008  # mip.msip = 1
.
csr 344 = 0000000000000000  # mip.msip = 0
. 10000
pc
m 10000
m 10008
m 10010

csr 344 = 0000000000000010  # mip.utip = 1
.
csr 344 = 0000000000000000  # mip.utip = 0
. 10000
csr 344 = 0000000000000010  # mip.utip = 1
.
csr 344 = 0000000000000000  # mip.utip = 0
. 10000
csr 344 = 0000000000000010  # mip.utip = 1
.
csr 344 = 0000000000000000  # mip.utip = 0
. 10000
pc
m 10000
m 10008
m 10010

csr 344 = 0000000000000080  # mip.mtip = 1
.
csr 344 = 0000000000000000  # mip.mtip = 0
. 10000
csr 344 = 0000000000000080  # mip.mtip = 1
.
csr 344 = 0000000000000000  # mip.mtip = 0
. 10000
csr 344 = 0000000000000080  # mip.mtip = 1
.
csr 344 = 0000000000000000  # mip.mtip = 0
. 10000
csr 344 = 0000000000000080  # mip.mtip = 1
.
csr 344 = 0000000000000000  # mip.mtip = 0
. 10000
pc
m 10000
m 10008
m 10010

csr 344 = 0000000000000100  # mip.ueip = 1
.
csr 344 = 0000000000000000  # mip.ueip = 0
. 10000
csr 344 = 0000000000000100  # mip.ueip = 1
.
csr 344 = 0000000000000000  # mip.ueip = 0
. 10000
csr 344 = 0000000000000100  # mip.ueip = 1
.
csr 344 = 0000000000000000  # mip.ueip = 0
. 10000
csr 344 = 0000000000000100  # mip.ueip = 1
.
csr 344 = 0000000000000000  # mip.ueip = 0
. 10000
csr 344 = 0000000000000100  # mip.ueip = 1
.
csr 344 = 0000000000000000  # mip.ueip = 0
. 10000
pc
m 10000
m 10008
m 10010

csr 344 = 0000000000000800  # mip.meip = 1
.
csr 344 = 0000000000000000  # mip.meip = 0
. 10000
csr 344 = 0000000000000800  # mip.meip = 1
.
csr 344 = 0000000000000000  # mip.meip = 0
. 10000
csr 344 = 0000000000000800  # mip.meip = 1
.
csr 344 = 0000000000000000  # mip.meip = 0
. 10000
csr 344 = 0000000000000800  # mip.meip = 1
.
csr 344 = 0000000000000000  # mip.meip = 0
. 10000
csr 344 = 0000000000000800  # mip.meip = 1
.
csr 344 = 0000000000000000  # mip.meip = 0
. 10000
csr 344 = 0000000000000800  # mip.meip = 1
.
csr 344 = 0000000000000000  # mip.meip = 0
. 10000
pc
m 10000
m 10008
m 10010

csr 344 = 0000000000000888  # mip.meip = 1, mip.mtip = 1, mip.msip = 1
b 3a8  # interrupt_handler_machine_external_int
. 1000
csr 344 = 0000000000000088  # mip.meip = 0, mip.mtip = 1, mip.msip = 1
b 2e8  # interrupt_handler_machine_software_int
. 1000
csr 344 = 0000000000000080  # mip.meip = 0, mip.mtip = 1, mip.msip = 0
b 348  # interrupt_handler_machine_timer_int
. 1000
csr 344 = 0000000000000000  # mip.meip = 0, mip.mtip = 0, mip.msip = 0
b 0
. 10000
pc
m 10000
m 10008
m 10010

b 0
. 1000000
x10
m 10000
m 10008
m 10010
