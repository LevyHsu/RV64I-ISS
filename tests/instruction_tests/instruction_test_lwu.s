	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# Load positive value, zero offset, base doubleword aligned

	la		t0, pos+8
	lwu		t1, 0(t0)
	TEST_EXPECT	t1, 0x000000003b3a3938

	# Load positive value, positive offset, base doubleword aligned

	la		t0, pos+8
	lwu		t1, 4(t0)
	TEST_EXPECT	t1, 0x000000003f3e3d3c

	# Load positive value, negative offset, base doubleword aligned

	la		t0, pos+8
	lwu		t1, -4(t0)
	TEST_EXPECT	t1, 0x0000000037363534

	# Load positive value, zero offset, base not doubleword aligned

	la		t0, pos+4
	lwu		t1, 0(t0)
	TEST_EXPECT	t1, 0x0000000037363534

	# Load positive value, positive offset, base not doubleword aligned

	la		t0, pos+4
	lwu		t1, 4(t0)
	TEST_EXPECT	t1, 0x000000003b3a3938

	# Load positive value, negative offset, base not doubleword aligned

	la		t0, pos+4
	lwu		t1, -4(t0)
	TEST_EXPECT	t1, 0x0000000033323130

	# ################################################################

	# Load negative value, zero offset, base doubleword aligned

	la		t0, neg+8
	lwu		t1, 0(t0)
	TEST_EXPECT	t1, 0x00000000fbfaf9f8

	# Load negative value, positive offset, base doubleword aligned

	la		t0, neg+8
	lwu		t1, 4(t0)
	TEST_EXPECT	t1, 0x00000000fffefdfc

	# Load negative value, negative offset, base doubleword aligned

	la		t0, neg+8
	lwu		t1, -4(t0)
	TEST_EXPECT	t1, 0x00000000f7f6f5f4

	# Load negative value, zero offset, base not doubleword aligned

	la		t0, neg+4
	lwu		t1, 0(t0)
	TEST_EXPECT	t1, 0x00000000f7f6f5f4

	# Load negative value, positive offset, base not doubleword aligned

	la		t0, neg+4
	lwu		t1, 4(t0)
	TEST_EXPECT	t1, 0x00000000fbfaf9f8

	# Load negative value, negative offset, base not doubleword aligned

	la		t0, neg+4
	lwu		t1, -4(t0)
	TEST_EXPECT	t1, 0x00000000f3f2f1f0


	TEST_END

	.data
	.align	2
	
pos:	.byte	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37
	.byte	0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f
	
neg:	.byte	0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7
	.byte	0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
	
	
