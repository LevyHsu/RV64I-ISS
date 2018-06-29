	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# Test positive value
	auipc		t0, 0x00001
	jal		t1, 1f
1:	sub		t1, t0, t1
	TEST_EXPECT	t1, 0x0000000000001000 - 8
	
	# Test positive value
	auipc		t0, 0x5A6B7
	jal		t1, 1f
1:	sub		t1, t0, t1
	TEST_EXPECT	t1, 0x000000005A6B7000 - 8

	# Test negative value
	auipc		t0, 0xA5B6C
	jal		t1, 1f
1:	sub		t1, t0, t1
	TEST_EXPECT	t1, 0xFFFFFFFFA5B6C000 - 8

	# Test value overwrites previous content
	lui		t0, 0xAAAAA
	addi            t0, t0, 0x555
	TEST_EXPECT	t0, 0xFFFFFFFFAAAAA555
	auipc		t0, 0x00000
	jal		t1, 1f
1:	sub		t1, t0, t1
	TEST_EXPECT	t1, 0x0000000000000000 - 8

	TEST_END
