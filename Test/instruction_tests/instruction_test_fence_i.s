	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# Test that self-modified code is fetched properly
	li		t0, 0x09900313	# addi t1, zero, 0x099
	la		t2, instr
	sw		t0, 0(t2)
	fence.i

instr:	addi		t1, zero, 0x055

	TEST_EXPECT	t1, 0x00000099

	TEST_END
