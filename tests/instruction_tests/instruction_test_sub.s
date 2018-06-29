	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# Test positive/zero value
	li		t0, 0x5A5A5A5A5A5A5A5A
	sub		t1, t0, zero
	TEST_EXPECT	t1, 0x5A5A5A5A5A5A5A5A

	# Test positive/positive value
	li		t0, 0x5A5A5A5A5A5A5A5A
	li		t1, 16
	sub		t2, t0, t1
	TEST_EXPECT	t2, 0x5A5A5A5A5A5A5A4A

	# Test positive/negative value, no overflow
	li		t0, 0x5A5A5A5A5A5A5A5A
	li		t1, -16
	sub		t2, t0, t1
	TEST_EXPECT	t2, 0x5A5A5A5A5A5A5A6A

	# Test positive/negative value, overflow
	li		t0, 0x7FFFFFFFFFFFFFFF
	li		t1, -16
	sub		t2, t0, t1
	TEST_EXPECT	t2, 0x800000000000000F

	# ################################################################

	# Test negative/zero value
	li		t0, 0xA5A5A5A5A5A5A5A5
	sub		t2, t0, zero
	TEST_EXPECT	t2, 0xA5A5A5A5A5A5A5A5

	# Test negative/negative value
	li		t0, 0xA5A5A5A5A5A5A5A5
	li		t1, -16
	sub		t2, t0, t1
	TEST_EXPECT	t2, 0xA5A5A5A5A5A5A5B5
	
	# Test negative/positive value, no overflow
	li		t0, 0xA5A5A5A5A5A5A5A5
	li		t1, 16
	sub		t2, t0, t1
	TEST_EXPECT	t2, 0xA5A5A5A5A5A5A595

	# Test negative/positive value, overflow
	li		t0, 0x800000000000000F
	li		t1, 16
	sub		t2, t0, t1
	TEST_EXPECT	t2, 0x7FFFFFFFFFFFFFFF

	# ################################################################

	# Test with x0 as destination
	li		t0, 0x5A5A5A5A5A5A5A5A
	li		t1, 16
	sub		zero, t0, t1
	TEST_EXPECT	zero, 0x0000000000000000
	

	TEST_END
