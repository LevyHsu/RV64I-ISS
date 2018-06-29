	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# Test positive value
	lui		t0, 0x00001
	TEST_EXPECT	t0, 0x0000000000001000

	# Test positive value
	lui		t1, 0x5A6B7
	TEST_EXPECT	t1, 0x000000005A6B7000

	# Test negative value
	lui		t2, 0xA5B6C
	TEST_EXPECT	t2, 0xFFFFFFFFA5B6C000

	# Test value overwrites previous content
	lui		t4, 0xAAAAA
	addi            t4, t4, 0x555
	TEST_EXPECT	t4, 0xFFFFFFFFAAAAA555
	lui		t4, 0x00000
	TEST_EXPECT	t4, 0x0000000000000000

	TEST_END
