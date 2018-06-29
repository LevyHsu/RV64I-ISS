	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# ################################################################
	# True result

	# positive arguments

	li		s0, 1000
	sltiu		s2, s0, 2000
	TEST_EXPECT	s2, 1

	# negative arguments

	li		s0, -2000
	sltiu		s2, s0, -1000
	TEST_EXPECT	s2, 1
	
	# positive/negative arguments

	li		s0, 1000
	sltiu		s2, s0, -1000
	TEST_EXPECT	s2, 1

	# zero/positive arguments

	li		s0, 0
	sltiu		s2, s0, 1000
	TEST_EXPECT	s2, 1

	# zero/negative arguments

	li		s0, 0
	sltiu		s2, s0, -1000
	TEST_EXPECT	s2, 1
	

	# ################################################################
	# False result

	# positive arguments

	li		s0, 2000
	sltiu		s2, s0, 1000
	TEST_EXPECT	s2, 0

	# negative arguments

	li		s0, -1000
	sltiu		s2, s0, -2000
	TEST_EXPECT	s2, 0
	
	# negative/positive arguments
	
	li		s0, -1000
	sltiu		s2, s0, 1000
	TEST_EXPECT	s2, 0
	
	# positive/zero arguments

	li		s0, 1000
	sltiu		s2, s0, 0
	TEST_EXPECT	s2, 0
	
	# negative/zero arguments

	li		s0, -1000
	sltiu		s2, s0, 0
	TEST_EXPECT	s2, 0
	
	# equal positive

	li		s0, 1000
	sltiu		s2, s0, 1000
	TEST_EXPECT	s2, 0
	
	# equal negative

	li		s0, -1000
	sltiu		s2, s0, -1000
	TEST_EXPECT	s2, 0
	
	# equal zero

	li		s0, 0
	sltiu		s2, s0, 0
	TEST_EXPECT	s2, 0
	

	TEST_END
	
