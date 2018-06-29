	.include "test_defines.h"

	.text
	.align	2
	
	.globl	_start
_start:

	TEST_INIT

	# ################################################################
	# Branch taken, positive displacement

	# positive arguments

	li	s0, 0x05A5A5A5A5A5A5A5
	li	s1, 0x0A5A5A5A5A5A5A5A
	bgeu	s1, s0, L01_t
	TEST_FAIL
L01_t:	

	# negative arguments

	li	s0, 0xA5A5A5A5A5A5A5A5
	li	s1, 0xAA55AA55AA55AA55
	bgeu	s1, s0, L02_t
	TEST_FAIL
L02_t:	
	
	# positive/negative arguments

	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0xA5A5A5A5A5A5A5A5
	bgeu	s1, s0, L03_t
	TEST_FAIL
L03_t:	

	# zero/positive arguments

	li	s0, 0x0000000000000000
	li	s1, 0x5A5A5A5A5A5A5A5A
	bgeu	s1, s0, L04_t
	TEST_FAIL
L04_t:	

	# zero/negative arguments

	li	s0, 0x0000000000000000
	li	s1, 0xA5A5A5A5A5A5A5A5
	bgeu	s1, s0, L05_t
	TEST_FAIL
L05_t:	
	
	# equal positive

	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0x5A5A5A5A5A5A5A5A
	bgeu	s1, s0, L06_t
	TEST_FAIL
L06_t:	
	
	# equal negative

	li	s0, 0xA5A5A5A5A5A5A5A5
	li	s1, 0xA5A5A5A5A5A5A5A5
	bgeu	s1, s0, L07_t
	TEST_FAIL
L07_t:	
	
	# equal zero

	li	s0, 0x0000000000000000
	li	s1, 0x0000000000000000
	bgeu	s1, s0, L08_t
	TEST_FAIL
L08_t:	
	

	# ################################################################
	# Branch not taken, positive displacement

	# positive arguments

	li	s0, 0x0A5A5A5A5A5A5A5A
	li	s1, 0x05A5A5A5A5A5A5A5
	bgeu	s1, s0, L11_t
	jal	zero, L11
L11_t:	
	TEST_FAIL
L11:

	# negative arguments

	li	s0, 0xAA55AA55AA55AA55
	li	s1, 0xA5A5A5A5A5A5A5A5
	bgeu	s1, s0, L12_t
	jal	zero, L12
L12_t:	
	TEST_FAIL
L12:
	
	# negative/positive arguments
	
	li	s0, 0xA5A5A5A5A5A5A5A5
	li	s1, 0x5A5A5A5A5A5A5A5A
	bgeu	s1, s0, L13_t
	jal	zero, L13
L13_t:	
	TEST_FAIL
L13:
	
	# positive/zero arguments

	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0x0000000000000000
	bgeu	s1, s0, L14_t
	jal	zero, L14
L14_t:	
	TEST_FAIL
L14:
	
	# negative/zero arguments

	li	s0, 0xA5A5A5A5A5A5A5A5
	li	s1, 0x0000000000000000
	bgeu	s1, s0, L15_t
	jal	zero, L15
L15_t:	
	TEST_FAIL
L15:
	

	# ################################################################
	# Branch taken, negative displacement

	# positive arguments

	jal	zero, L21
L21_t:	jal	zero, L21_e
L21:	li	s0, 0x05A5A5A5A5A5A5A5
	li	s1, 0x0A5A5A5A5A5A5A5A
	bgeu	s1, s0, L21_t
	TEST_FAIL
L21_e:	

	# negative arguments

	jal	zero, L22
L22_t:	jal	zero, L22_e
L22:	li	s0, 0xA5A5A5A5A5A5A5A5
	li	s1, 0xAA55AA55AA55AA55
	bgeu	s1, s0, L22_t
	TEST_FAIL
L22_e:	
	
	# positive/negative arguments

	jal	zero, L23
L23_t:	jal	zero, L23_e
L23:	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0xA5A5A5A5A5A5A5A5
	bgeu	s1, s0, L23_t
	TEST_FAIL
L23_e:	

	# zero/positive arguments

	jal	zero, L24
L24_t:	jal	zero, L24_e
L24:	li	s0, 0x0000000000000000
	li	s1, 0x5A5A5A5A5A5A5A5A
	bgeu	s1, s0, L24_t
	TEST_FAIL
L24_e:	

	# zero/negative arguments

	jal	zero, L25
L25_t:	jal	zero, L25_e
L25:	li	s0, 0x0000000000000000
	li	s1, 0xA5A5A5A5A5A5A5A5
	bgeu	s1, s0, L25_t
	TEST_FAIL
L25_e:	
	
	# equal positive

	jal	zero, L26
L26_t:	jal	zero, L26_e
L26:	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0x5A5A5A5A5A5A5A5A
	bgeu	s1, s0, L26_t
	TEST_FAIL
L26_e:	
	
	# equal negative

	jal	zero, L27
L27_t:	jal	zero, L27_e
L27:	li	s0, 0xA5A5A5A5A5A5A5A5
	li	s1, 0xA5A5A5A5A5A5A5A5
	bgeu	s1, s0, L27_t
	TEST_FAIL
L27_e:	
	
	# equal zero

	jal	zero, L28
L28_t:	jal	zero, L28_e
L28:	li	s0, 0x0000000000000000
	li	s1, 0x0000000000000000
	bgeu	s1, s0, L28_t
	TEST_FAIL
L28_e:	
	

	# ################################################################
	# Branch not taken, negative displacement

	# positive arguments

	jal	zero, L31
L31_t:
	TEST_FAIL
L31:	li	s0, 0x0A5A5A5A5A5A5A5A
	li	s1, 0x05A5A5A5A5A5A5A5
	bgeu	s1, s0, L31_t

	# negative arguments

	jal	zero, L32
L32_t:
	TEST_FAIL
L32:	li	s0, 0xAA55AA55AA55AA55
	li	s1, 0xA5A5A5A5A5A5A5A5
	bgeu	s1, s0, L32_t
	
	# negative/positive arguments
	
	jal	zero, L33
L33_t:
	TEST_FAIL
L33:	li	s0, 0xA5A5A5A5A5A5A5A5
	li	s1, 0x5A5A5A5A5A5A5A5A
	bgeu	s1, s0, L33_t
	
	# positive/zero arguments

	jal	zero, L34
L34_t:
	TEST_FAIL
L34:	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0x0000000000000000
	bgeu	s1, s0, L34_t
	
	# negative/zero arguments

	jal	zero, L35
L35_t:
	TEST_FAIL
L35:	li	s0, 0xA5A5A5A5A5A5A5A5
	li	s1, 0x0000000000000000
	bgeu	s1, s0, L35_t
	

	TEST_END
	
