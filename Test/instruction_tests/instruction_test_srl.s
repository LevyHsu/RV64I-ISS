	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# Test positive value, zero shift
	li		t0, 0x5A6B7C8D12345678
	li		t2, 0
	srl		t1, t0, t2
	TEST_EXPECT	t1, 0x5A6B7C8D12345678

	# Test positive value, non-zero shift
	li		t0, 0x5A6B7C8D12345678
	li		t2, 4
	srl		t1, t0, t2
	TEST_EXPECT	t1, 0x05A6B7C8D1234567

	# Test positive value, non-zero shift
	li		t0, 0x5A6B7C8D12345678
	li		t2, 48
	srl		t1, t0, t2
	TEST_EXPECT	t1, 0x0000000000005A6B

	# Test positive value, non-zero shift, rs2 > 63
	li		t0, 0x5A6B7C8D12345678
	li		t2, 80
	srl		t1, t0, t2
	TEST_EXPECT	t1, 0x00005A6B7C8D1234

	# Test negative value, zero shift
	li		t0, 0xA5B6C7D812345678
	li		t2, 0
	srl		t1, t0, t2
	TEST_EXPECT	t1, 0xA5B6C7D812345678

	# Test negative value, non-zero shift
	li		t0, 0xA5B6C7D812345678
	li		t2, 4
	srl		t1, t0, t2
	TEST_EXPECT	t1, 0x0A5B6C7D81234567

	# Test negative value, non-zero shift
	li		t0, 0xA5B6C7D812345678
	li		t2, 48
	srl		t1, t0, t2
	TEST_EXPECT	t1, 0x000000000000A5B6

	# Test negative value, non-zero shift
	li		t0, 0xA5B6C7D812345678
	li		t2, 80
	srl		t1, t0, t2
	TEST_EXPECT	t1, 0x0000A5B6C7D81234

	# ################################################################

	# Test with x0 as destination
	li		t0, 0xA5B6C7D812345678
	li		t2, 20
	srl		zero, t0, t2
	TEST_EXPECT	zero, 0x0000000000000000
	

	TEST_END
