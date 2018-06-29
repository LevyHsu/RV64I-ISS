	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# Test zero value

	li		t0, 0x5A5A5A5A5A5A5A5A
	xori		t1, t0, 0
	TEST_EXPECT	t1, 0x5A5A5A5A5A5A5A5A

	li		t0, 0xA5A5A5A5A5A5A5A5
	xori		t1, t0, 0
	TEST_EXPECT	t1, 0xA5A5A5A5A5A5A5A5

	# Test positive value

	li		t0, 0x5A5A5A5A5A5A5A5A
	xori		t1, t0, 0x00F
	TEST_EXPECT	t1, 0x5A5A5A5A5A5A5A55

	li		t0, 0xA5A5A5A5A5A5A5A5
	xori		t1, t0, 0x00F
	TEST_EXPECT	t1, 0xA5A5A5A5A5A5A5AA

	# Test negative value

	li		t0, 0x5A5A5A5A5A5A5A5A
	xori		t1, t0, -241  # 0xF0F
	TEST_EXPECT	t1, 0xA5A5A5A5A5A5A555

	li		t0, 0xA5A5A5A5A5A5A5A5
	xori		t1, t0, -241  # 0xF0F
	TEST_EXPECT	t1, 0x5A5A5A5A5A5A5AAA

	# ################################################################

	# Test with x0 as destination

	li		t0, 0x5A5A5A5A5A5A5A5A
	xori		zero, t0, 0x00F
	TEST_EXPECT	zero, 0x0000000000000000
	

	TEST_END
