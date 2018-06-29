	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# Test no effect on t0
	li		t0, 0x5A5A5A5A5A5A5A5A
	ecall
	TEST_EXPECT	t0, 0x5A5A5A5A5A5A5A5A

	TEST_END
