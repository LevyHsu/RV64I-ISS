	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# Test branch taken, positive displacement

	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0xA5A5A5A5A5A5A5A5
	bne	s0, s1, L1_t
	TEST_FAIL
L1_t:	

	li	s2, 0xA5A5A5A5A5A5A5A5
	li	s3, 0x5A5A5A5A5A5A5A5A
	bne	s2, s3, L2_t
	TEST_FAIL
L2_t:	

	# Test branch not taken, positive displacement

	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0x5A5A5A5A5A5A5A5A
	bne	s0, s1, L3_t
	jal	zero, L3
L3_t:	
	TEST_FAIL
L3:
	
	li	s2, 0x5A5A5A5A5A5A5A5A
	li	s3, 0x5A5A5A5A5A5A5A5A
	bne	s2, s3, L4_t
	jal	zero, L4
L4_t:	
	TEST_FAIL
L4:
	
	# Test branch taken, negative displacement

	jal	zero, L5
L5_t:	jal	zero, L5_e
L5:	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0xA5A5A5A5A5A5A5A5
	bne	s0, s1, L5_t
	TEST_FAIL
L5_e:	

	jal	zero, L6
L6_t:	jal	zero, L6_e
L6:	li	s2, 0xA5A5A5A5A5A5A5A5
	li	s3, 0x5A5A5A5A5A5A5A5A
	bne	s2, s3, L6_t
	TEST_FAIL
L6_e:	

	# Test branch not taken, negative displacement

	jal	zero, L7
L7_t:
	TEST_FAIL
L7:	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0x5A5A5A5A5A5A5A5A
	bne	s0, s1, L7_t
	
	jal	zero, L8
L8_t:
	TEST_FAIL
L8:	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0x5A5A5A5A5A5A5A5A
	bne	s0, s1, L8_t
	
	TEST_END
	
