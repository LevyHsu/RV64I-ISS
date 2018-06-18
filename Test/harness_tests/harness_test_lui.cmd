# lui instruction format: iiii iiii iiii iiii iiii dddd d011 0111

# Test with positive immediate
x1 = 1111111111111111
m 0000000000002000 = 5A5A6137	# lui x2, 0x5A5A6
pc = 0000000000002000
.
x2	# expect 0x000000005A5A6000

# Test with negative immediate
x1 = 1111111111111111
m 0000000000002010 = A5A53137	# lui x2, 0xA5A53
pc = 0000000000002010
.
x2	# expect 0xFFFFFFFFA5A53000

