	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# ################################################################
	# True result

	# positive arguments

	li		s0, 0x05A5A5A5A5A5A5A5
	li		s1, 0x0A5A5A5A5A5A5A5A
	slt		s2, s0, s1
	TEST_EXPECT	s2, 1

	# negative arguments

	li		s0, 0xA5A5A5A5A5A5A5A5
	li		s1, 0xAA55AA55AA55AA55
	slt		s2, s0, s1
	TEST_EXPECT	s2, 1
	
	# negative/positive arguments

	li		s0, 0xA5A5A5A5A5A5A5A5
	li		s1, 0x5A5A5A5A5A5A5A5A
	slt		s2, s0, s1
	TEST_EXPECT	s2, 1

	# zero/positive arguments

	li		s0, 0x0000000000000000
	li		s1, 0x5A5A5A5A5A5A5A5A
	slt		s2, s0, s1
	TEST_EXPECT	s2, 1

	# negative/zero arguments

	li		s0, 0xA5A5A5A5A5A5A5A5
	li		s1, 0x0000000000000000
	slt		s2, s0, s1
	TEST_EXPECT	s2, 1
	

	# ################################################################
	# False result

	# positive arguments

	li		s0, 0x0A5A5A5A5A5A5A5A
	li		s1, 0x05A5A5A5A5A5A5A5
	slt		s2, s0, s1
	TEST_EXPECT	s2, 0

	# negative arguments

	li		s0, 0xAA55AA55AA55AA55
	li		s1, 0xA5A5A5A5A5A5A5A5
	slt		s2, s0, s1
	TEST_EXPECT	s2, 0
	
	# positive/negative arguments
	
	li		s0, 0x5A5A5A5A5A5A5A5A
	li		s1, 0xA5A5A5A5A5A5A5A5
	slt		s2, s0, s1
	TEST_EXPECT	s2, 0
	
	# positive/zero arguments

	li		s0, 0x5A5A5A5A5A5A5A5A
	li		s1, 0x0000000000000000
	slt		s2, s0, s1
	TEST_EXPECT	s2, 0
	
	# zero/negative arguments

	li		s0, 0x0000000000000000
	li		s1, 0xA5A5A5A5A5A5A5A5
	slt		s2, s0, s1
	TEST_EXPECT	s2, 0
	
	# equal positive

	li		s0, 0x5A5A5A5A5A5A5A5A
	li		s1, 0x5A5A5A5A5A5A5A5A
	slt		s2, s0, s1
	TEST_EXPECT	s2, 0
	
	# equal negative

	li		s0, 0xA5A5A5A5A5A5A5A5
	li		s1, 0xA5A5A5A5A5A5A5A5
	slt		s2, s0, s1
	TEST_EXPECT	s2, 0
	
	# equal zero

	li		s0, 0x0000000000000000
	li		s1, 0x0000000000000000
	slt		s2, s0, s1
	TEST_EXPECT	s2, 0
	

	TEST_END
	
