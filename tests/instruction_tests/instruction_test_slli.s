	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# Test positive value, zero shift
	li		t0, 0x5A6B7C8D12345678
	slli		t1, t0, 0
	TEST_EXPECT	t1, 0x5A6B7C8D12345678

	# Test positive value, non-zero shift
	li		t0, 0x5A6B7C8D12345678
	slli		t1, t0, 4
	TEST_EXPECT	t1, 0xA6B7C8D123456780

	# Test positive value, non-zero shift
	li		t0, 0x5A6B7C8D12345678
	slli		t1, t0, 16
	TEST_EXPECT	t1, 0x7C8D123456780000

	# Test positive value, non-zero shift
	li		t0, 0x5A6B7C8D12345678
	slli		t1, t0, 32
	TEST_EXPECT	t1, 0x1234567800000000

	# Test positive value, non-zero shift
	li		t0, 0x5A6B7C8D12345678
	slli		t1, t0, 48
	TEST_EXPECT	t1, 0x5678000000000000

	# Test negative value, zero shift
	li		t0, 0xA5B6C7D812345678
	slli		t1, t0, 0
	TEST_EXPECT	t1, 0xA5B6C7D812345678

	# Test negative value, non-zero shift
	li		t0, 0xA5B6C7D812345678
	slli		t1, t0, 4
	TEST_EXPECT	t1, 0x5B6C7D8123456780

	# Test negative value, non-zero shift
	li		t0, 0xA5B6C7D812345678
	slli		t1, t0, 16
	TEST_EXPECT	t1, 0xC7D8123456780000

	# Test negative value, non-zero shift
	li		t0, 0xA5B6C7D812345678
	slli		t1, t0, 32
	TEST_EXPECT	t1, 0x1234567800000000

	# Test negative value, non-zero shift
	li		t0, 0xA5B6C7D812345678
	slli		t1, t0, 48
	TEST_EXPECT	t1, 0x5678000000000000

	# ################################################################

	# Test with x0 as destination
	li		t0, 0xA5B6C7D812345678
	slli		zero, t0, 20
	TEST_EXPECT	zero, 0x0000000000000000
	

	TEST_END
