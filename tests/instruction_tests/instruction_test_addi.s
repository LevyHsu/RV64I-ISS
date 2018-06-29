	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# Test positive/zero value
	li		t0, 0x5A5A5A5A5A5A5A5A
	addi		t1, t0, 0
	TEST_EXPECT	t1, 0x5A5A5A5A5A5A5A5A

	# Test positive/positive value, no overflow
	li		t0, 0x5A5A5A5A5A5A5A5A
	addi		t1, t0, 16
	TEST_EXPECT	t1, 0x5A5A5A5A5A5A5A6A

	# Test positive/negative value
	li		t0, 0x5A5A5A5A5A5A5A5A
	addi		t1, t0, -16
	TEST_EXPECT	t1, 0x5A5A5A5A5A5A5A4A

	# Test positive/positive value, overflow
	li		t0, 0x7FFFFFFFFFFFFFFF
	addi		t1, t0, 16
	TEST_EXPECT	t1, 0x800000000000000F

	# ################################################################

	# Test negative/zero value
	li		t0, 0xA5A5A5A5A5A5A5A5
	addi		t1, t0, 0
	TEST_EXPECT	t1, 0xA5A5A5A5A5A5A5A5

	# Test negative/positive value
	li		t0, 0xA5A5A5A5A5A5A5A5
	addi		t1, t0, 16
	TEST_EXPECT	t1, 0xA5A5A5A5A5A5A5B5
	
	# Test negative/negative value, no overflow
	li		t0, 0xA5A5A5A5A5A5A5A5
	addi		t1, t0, -16
	TEST_EXPECT	t1, 0xA5A5A5A5A5A5A595

	# Test negative/negative value, overflow
	li		t0, 0x800000000000000F
	addi		t1, t0, -16
	TEST_EXPECT	t1, 0x7FFFFFFFFFFFFFFF

	# ################################################################

	# Test with x0 as destination
	li		t0, 0x5A5A5A5A5A5A5A5A
	addi		zero, t0, 16
	TEST_EXPECT	zero, 0x0000000000000000
	

	TEST_END
