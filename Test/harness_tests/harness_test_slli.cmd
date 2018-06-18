# slli instruction format: 0000 00ii iiii ssss s001 dddd d001 0011

# Tests with different source and destination registers

# Test with small non-zero shift
x1 = 0123456789ABCDEF
m 0000000000002000 = 00809113	# slli x2, x1, 8
pc = 0000000000002000
.
x2	# expect 23456789ABCDEF00

# Test with large non-zero shift
x1 = 0123456789ABCDEF
m 0000000000002000 = 03009113	# slli x2, x1, 48
pc = 0000000000002000
.
x2	# expect CDEF000000000000

# Test with zero shift
x1 = 0123456789ABCDEF
m 0000000000002000 = 00009113	# slli x2, x1, 0
pc = 0000000000002000
.
x2	# expect 0123456789ABCDEF

# Tests with same source and destination registers

# Test with small non-zero shift
x9 = 0123456789ABCDEF
m 0000000000002000 = 00849493	# slli x9, x9, 8
pc = 0000000000002000
.
x9	# expect 23456789ABCDEF00

# Test with large non-zero shift
x9 = 0123456789ABCDEF
m 0000000000002000 = 03049493	# slli x9, x9, 48
pc = 0000000000002000
.
x9	# expect CDEF000000000000

# Test with zero shift
x9 = 0123456789ABCDEF
m 0000000000002000 = 00049493	# slli x9, x9, 0
pc = 0000000000002000
.
x9	# expect 0123456789ABCDEF

