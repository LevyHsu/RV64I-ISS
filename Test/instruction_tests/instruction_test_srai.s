	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# Test positive value, zero shift
	li		t0, 0x5A6B7C8D12345678
	srai		t1, t0, 0
	TEST_EXPECT	t1, 0x5A6B7C8D12345678

	# Test positive value, non-zero shift
	li		t0, 0x5A6B7C8D12345678
	srai		t1, t0, 4
	TEST_EXPECT	t1, 0x05A6B7C8D1234567

	# Test positive value, non-zero shift
	li		t0, 0x5A6B7C8D12345678
	srai		t1, t0, 16
	TEST_EXPECT	t1, 0x00005A6B7C8D1234

	# Test positive value, non-zero shift
	li		t0, 0x5A6B7C8D12345678
	srai		t1, t0, 32
	TEST_EXPECT	t1, 0x000000005A6B7C8D

	# Test positive value, non-zero shift
	li		t0, 0x5A6B7C8D12345678
	srai		t1, t0, 48
	TEST_EXPECT	t1, 0x0000000000005A6B

	# Test negative value, zero shift
	li		t0, 0xA5B6C7D812345678
	srai		t1, t0, 0
	TEST_EXPECT	t1, 0xA5B6C7D812345678

	# Test negative value, non-zero shift
	li		t0, 0xA5B6C7D812345678
	srai		t1, t0, 4
	TEST_EXPECT	t1, 0xFA5B6C7D81234567

	# Test negative value, non-zero shift
	li		t0, 0xA5B6C7D812345678
	srai		t1, t0, 16
	TEST_EXPECT	t1, 0xFFFFA5B6C7D81234

	# Test negative value, non-zero shift
	li		t0, 0xA5B6C7D812345678
	srai		t1, t0, 32
	TEST_EXPECT	t1, 0xFFFFFFFFA5B6C7D8

	# Test negative value, non-zero shift
	li		t0, 0xA5B6C7D812345678
	srai		t1, t0, 48
	TEST_EXPECT	t1, 0xFFFFFFFFFFFFA5B6

	# ################################################################

	# Test with x0 as destination
	li		t0, 0xA5B6C7D812345678
	srai		zero, t0, 20
	TEST_EXPECT	zero, 0x0000000000000000
	

	TEST_END
