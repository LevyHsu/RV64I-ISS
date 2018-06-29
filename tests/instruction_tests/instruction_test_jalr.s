	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	jal		t0, L1
L1:	lui		t1, %hi(L1_t)
	jalr		t1, t1, %lo(L1_t)
	TEST_FAIL
L1_t:	sub		t1, t1, t0
	TEST_EXPECT	t1, 8

	jal		t0, L2
L2:	lui		t2, %hi(L2_t)
	jalr		t2, t2, %lo(L2_t)
	TEST_FAIL

L3_t:	sub		t3, t3, t0
	TEST_EXPECT	t3, 8

	lui		t4, %hi(L4_t)
L4:	jalr		zero, t4, %lo(L4_t)
	TEST_FAIL

L2_t:	sub		t2, t2, t0
	TEST_EXPECT	t2, 8

	jal		t0, L3
L3:	lui		t3, %hi(L3_t)
	jalr		t3, t3, %lo(L3_t)
	TEST_FAIL

L4_t:	TEST_EXPECT	zero, 0x0000000000000000

	TEST_END
	
