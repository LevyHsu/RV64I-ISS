	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	jal		t0, L1
L1:	jal		t1, L1_t
	TEST_FAIL
L1_t:	sub		t1, t1, t0
	TEST_EXPECT	t1, 4

	jal		t0, L2
L2:	jal		t2, L2_t
	TEST_FAIL

L3_t:	sub		t3, t3, t0
	TEST_EXPECT	t3, 4

L4:	jal		zero, L4_t
	TEST_FAIL

L2_t:	sub		t2, t2, t0
	TEST_EXPECT	t2, 4

	jal		t0, L3
L3:	jal		t3, L3_t
	TEST_FAIL

L4_t:	TEST_EXPECT	zero, 0x0000000000000000

	TEST_END
	
