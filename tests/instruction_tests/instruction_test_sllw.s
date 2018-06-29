	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# Test positive value, zero shift
	li		t0, 0x123456785A6B7C8D
	li		t2, 0
	sllw		t1, t0, t2
	TEST_EXPECT	t1, 0x000000005A6B7C8D

	# Test positive value, non-zero shift, positive result
	li		t0, 0x123456785A6B7C8D
	li		t2, 8
	sllw		t1, t0, t2
	TEST_EXPECT	t1, 0x000000006B7C8D00

	# Test positive value, non-zero shift, negative result
	li		t0, 0x123456785A6B7C8D
	li		t2, 20
	sllw		t1, t0, t2
	TEST_EXPECT	t1, 0xFFFFFFFFC8D00000

	# Test positive value, non-zero shift, positive result
	li		t0, 0x123456785A6B7C8D
	li		t2, 48
	sllw		t1, t0, t2
	TEST_EXPECT	t1, 0x000000007C8D0000

	# Test positive value, non-zero shift, negative result
	li		t0, 0x123456785A6B7C8D
	li		t2, 44
	sllw		t1, t0, t2
	TEST_EXPECT	t1, 0xFFFFFFFFB7C8D000

	# Test negative value, zero shift
	li		t0, 0x12345678A5B6C7D8
	li		t2, 0
	sllw		t1, t0, t2
	TEST_EXPECT	t1, 0xFFFFFFFFA5B6C7D8

	# Test negative value, non-zero shift, negative result
	li		t0, 0x12345678A5B6C7D8
	li		t2, 8
	sllw		t1, t0, t2
	TEST_EXPECT	t1, 0xFFFFFFFFB6C7D800

	# Test negative value, non-zero shift, positive result
	li		t0, 0x12345678A5B6C7D8
	li		t2, 20
	sllw		t1, t0, t2
	TEST_EXPECT	t1, 0x000000007D800000

	# Test negative value, non-zero shift, negative result
	li		t0, 0x12345678A5B6C7D8
	li		t2, 48
	sllw		t1, t0, t2
	TEST_EXPECT	t1, 0xFFFFFFFFC7D80000

	# Test negative value, non-zero shift, positive result
	li		t0, 0x12345678A5B6C7D8
	li		t2, 44
	sllw		t1, t0, t2
	TEST_EXPECT	t1, 0x000000006C7D8000

	# ################################################################

	# Test with x0 as destination
	li		t0, 0x12345678A5B6C7D8
	li		t2, 20
	sllw		zero, t0, t2
	TEST_EXPECT	zero, 0x0000000000000000
	

	TEST_END
