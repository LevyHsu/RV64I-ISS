	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# Test zero value
	
	li		t0, 0x5A5A5A5A5A5A5A5A
	and		t2, t0, zero
	TEST_EXPECT	t2, 0x0000000000000000

	li		t0, 0xA5A5A5A5A5A5A5A5
	and		t2, t0, zero
	TEST_EXPECT	t2, 0x0000000000000000

	li		t1, 0x5A5A5A5A5A5A5A5A
	and		t2, zero, t1
	TEST_EXPECT	t2, 0x0000000000000000

	li		t1, 0xA5A5A5A5A5A5A5A5
	and		t2, zero, t1
	TEST_EXPECT	t2, 0x0000000000000000

	# Test non-zero values
	
	li		t0, 0x5A5A5A5A5A5A5A5A
	li		t1, 0x0F0FF0F00F0FF0F0
	and		t2, t0, t1
	TEST_EXPECT	t2, 0x0A0A50500A0A5050

	li		t0, 0xA5A5A5A5A5A5A5A5
	li		t1, 0x0F0FF0F00F0FF0F0
	and		t2, t0, t1
	TEST_EXPECT	t2, 0x0505A0A00505A0A0

	# ################################################################

	# Test with x0 as destination
	
	li		t0, 0x5A5A5A5A5A5A5A5A
	li		t1, 0x0F0FF0F00F0FF0F0
	and		zero, t0, t1
	TEST_EXPECT	zero, 0x0000000000000000
	

	TEST_END
