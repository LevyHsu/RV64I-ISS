# addi instruction format: iiii iiii iiii ssss s000 dddd d001 0011

# Tests with different source and destination registers

# Test with positive immediate
x1 = 1111111111111000
m 0000000000002000 = 5A608113	# addi x2, x1, 0x5A6
pc = 0000000000002000
.
x2	# expect 11111111111115A6

# Test with negative immediate
x1 = 1111111111111000
m 0000000000002010 = A5308113	# addi x2, x1, 0xA53
pc = 0000000000002010
.
x2	# expect 1111111111110A53

# Tests with same source and destination registers

# Test with positive immediate
x9 = 1111111111111000
m 0000000000002020 = 5A648493	# addi x9, x9, 0x5A6
pc = 0000000000002020
.
x9	# expect 11111111111115A6

# Test with negative immediate
x9 = 1111111111111000
m 0000000000002030 = A5348493	# addi x9, x9, 0xA53
pc = 0000000000002030
.
x9	# expect 1111111111110A53

