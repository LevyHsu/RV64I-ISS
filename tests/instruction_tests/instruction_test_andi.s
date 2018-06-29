	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# Test zero value

	li		t0, 0x5A5A5A5A5A5A5A5A
	andi		t1, t0, 0
	TEST_EXPECT	t1, 0x0000000000000000

	li		t0, 0xA5A5A5A5A5A5A5A5
	andi		t1, t0, 0
	TEST_EXPECT	t1, 0x0000000000000000

	# Test positive value

	li		t0, 0x5A5A5A5A5A5A5A5A
	andi		t1, t0, 0x00F
	TEST_EXPECT	t1, 0x000000000000000A

	li		t0, 0xA5A5A5A5A5A5A5A5
	andi		t1, t0, 0x00F
	TEST_EXPECT	t1, 0x0000000000000005

	# Test negative value

	li		t0, 0x5A5A5A5A5A5A5A5A
	andi		t1, t0, -241  # 0xF0F
	TEST_EXPECT	t1, 0x5A5A5A5A5A5A5A0A

	li		t0, 0xA5A5A5A5A5A5A5A5
	andi		t1, t0, -241  # 0xF0F
	TEST_EXPECT	t1, 0xA5A5A5A5A5A5A505

	# ################################################################

	# Test with x0 as destination

	li		t0, 0x5A5A5A5A5A5A5A5A
	andi		zero, t0, 0x00F
	TEST_EXPECT	zero, 0x0000000000000000
	

	TEST_END
