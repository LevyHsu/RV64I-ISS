	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# Test positive value, zero shift
	li		t0, 0x123456785A6B7C8D
	srliw		t1, t0, 0
	TEST_EXPECT	t1, 0x000000005A6B7C8D

	# Test positive value, non-zero shift
	li		t0, 0x123456785A6B7C8D
	srliw		t1, t0, 8
	TEST_EXPECT	t1, 0x00000000005A6B7C

	# Test positive value, non-zero shift
	li		t0, 0x123456785A6B7C8D
	srliw		t1, t0, 20
	TEST_EXPECT	t1, 0x00000000000005A6

	# Test negative value, zero shift
	li		t0, 0x12345678A5B6C7D8
	srliw		t1, t0, 0
	TEST_EXPECT	t1, 0xFFFFFFFFA5B6C7D8

	# Test negative value, non-zero shift
	li		t0, 0x12345678A5B6C7D8
	srliw		t1, t0, 8
	TEST_EXPECT	t1, 0x0000000000A5B6C7

	# Test negative value, non-zero shift
	li		t0, 0x12345678A5B6C7D8
	srliw		t1, t0, 20
	TEST_EXPECT	t1, 0x0000000000000A5B

	# ################################################################

	# Test with x0 as destination
	li		t0, 0x12345678A5B6C7D8
	srliw		zero, t0, 20
	TEST_EXPECT	zero, 0x0000000000000000
	

	TEST_END
