	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	li		t0, 0x0909090909090909
	li		t1, 0x5A5A5A5A5A5A5A5A
	
	# Test no effect on registers
	
	csrrw		t1, marchid, t0
	TEST_EXPECT	t0, 0x0909090909090909
	TEST_EXPECT	t1, 0x5A5A5A5A5A5A5A5A

	csrrs		t1, marchid, t0
	TEST_EXPECT	t0, 0x0909090909090909
	TEST_EXPECT	t1, 0x5A5A5A5A5A5A5A5A

	csrrc		t1, marchid, t0
	TEST_EXPECT	t0, 0x0909090909090909
	TEST_EXPECT	t1, 0x5A5A5A5A5A5A5A5A

	csrrwi		t1, marchid, 0x09
	TEST_EXPECT	t1, 0x5A5A5A5A5A5A5A5A

	csrrsi		t1, marchid, 0x09
	TEST_EXPECT	t1, 0x5A5A5A5A5A5A5A5A

	csrrci		t1, marchid, 0x09
	TEST_EXPECT	t1, 0x5A5A5A5A5A5A5A5A

	TEST_END
