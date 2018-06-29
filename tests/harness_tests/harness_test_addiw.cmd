# addiw instruction format: iiii iiii iiii ssss s000 dddd d001 1011

# Tests with different source and destination registers

# Test with positive immediate, positive result
x1 = 1111111111111000
m 0000000000002000 = 5A60811b	# addiw x2, x1, 0x5A6
pc = 0000000000002000
.
x2	# expect 00000000111115A6

# Test with negative immediate, positive result
x1 = 1111111111111000
m 0000000000002010 = A530811b	# addiw x2, x1, 0xA53
pc = 0000000000002010
.
x2	# expect 0000000011110A53

# Test with positive immediate, negative result
x1 = 11111111F1111000
m 0000000000002000 = 5A60811b	# addiw x2, x1, 0x5A6
pc = 0000000000002000
.
x2	# expect FFFFFFFFF11115A6

# Test with negative immediate, negative result
x1 = 11111111F1111000
m 0000000000002010 = A530811b	# addiw x2, x1, 0xA53
pc = 0000000000002010
.
x2	# expect FFFFFFFFF1110A53

# Tests with same source and destination registers

# Test with positive immediate, positive result
x9 = 1111111111111000
m 0000000000002020 = 5A64849b	# addiw x9, x9, 0x5A6
pc = 0000000000002020
.
x9	# expect 00000000111115A6

# Test with negative immediate, positive result
x9 = 1111111111111000
m 0000000000002030 = A534849b	# addiw x9, x9, 0xA53
pc = 0000000000002030
.
x9	# expect 0000000011110A53

# Test with positive immediate, negative result
x9 = 11111111F1111000
m 0000000000002020 = 5A64849b	# addiw x9, x9, 0x5A6
pc = 0000000000002020
.
x9	# expect FFFFFFFFF11115A6

# Test with negative immediate, negative result
x9 = 11111111F1111000
m 0000000000002030 = A534849b	# addiw x9, x9, 0xA53
pc = 0000000000002030
.
x9	# expect FFFFFFFFF1110A53

