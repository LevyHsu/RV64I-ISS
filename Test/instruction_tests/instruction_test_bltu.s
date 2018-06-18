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
	bltu	s0, s1, L01_t
	TEST_FAIL
L01_t:	

	# negative arguments

	li	s0, 0xA5A5A5A5A5A5A5A5
	li	s1, 0xAA55AA55AA55AA55
	bltu	s0, s1, L02_t
	TEST_FAIL
L02_t:	
	
	# positive/negative arguments

	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0xA5A5A5A5A5A5A5A5
	bltu	s0, s1, L03_t
	TEST_FAIL
L03_t:	

	# zero/positive arguments

	li	s0, 0x0000000000000000
	li	s1, 0x5A5A5A5A5A5A5A5A
	bltu	s0, s1, L04_t
	TEST_FAIL
L04_t:	

	# zero/negative arguments

	li	s0, 0x0000000000000000
	li	s1, 0xA5A5A5A5A5A5A5A5
	bltu	s0, s1, L05_t
	TEST_FAIL
L05_t:	
	

	# ################################################################
	# Branch not taken, positive displacement

	# positive arguments

	li	s0, 0x0A5A5A5A5A5A5A5A
	li	s1, 0x05A5A5A5A5A5A5A5
	bltu	s0, s1, L11_t
	jal	zero, L11
L11_t:	
	TEST_FAIL
L11:

	# negative arguments

	li	s0, 0xAA55AA55AA55AA55
	li	s1, 0xA5A5A5A5A5A5A5A5
	bltu	s0, s1, L12_t
	jal	zero, L12
L12_t:	
	TEST_FAIL
L12:
	
	# negative/positive arguments
	
	li	s0, 0xA5A5A5A5A5A5A5A5
	li	s1, 0x5A5A5A5A5A5A5A5A
	bltu	s0, s1, L13_t
	jal	zero, L13
L13_t:	
	TEST_FAIL
L13:
	
	# positive/zero arguments

	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0x0000000000000000
	bltu	s0, s1, L14_t
	jal	zero, L14
L14_t:	
	TEST_FAIL
L14:
	
	# negative/zero arguments

	li	s0, 0xA5A5A5A5A5A5A5A5
	li	s1, 0x0000000000000000
	bltu	s0, s1, L15_t
	jal	zero, L15
L15_t:	
	TEST_FAIL
L15:
	
	# equal positive

	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0x5A5A5A5A5A5A5A5A
	bltu	s0, s1, L16_t
	jal	zero, L16
L16_t:	
	TEST_FAIL
L16:
	
	# equal negative

	li	s0, 0xA5A5A5A5A5A5A5A5
	li	s1, 0xA5A5A5A5A5A5A5A5
	bltu	s0, s1, L17_t
	jal	zero, L17
L17_t:	
	TEST_FAIL
L17:
	
	# equal zero

	li	s0, 0x0000000000000000
	li	s1, 0x0000000000000000
	bltu	s0, s1, L18_t
	jal	zero, L18
L18_t:	
	TEST_FAIL
L18:
	

	# ################################################################
	# Branch taken, negative displacement

	# positive arguments

	jal	zero, L21
L21_t:	jal	zero, L21_e
L21:	li	s0, 0x05A5A5A5A5A5A5A5
	li	s1, 0x0A5A5A5A5A5A5A5A
	bltu	s0, s1, L21_t
	TEST_FAIL
L21_e:	

	# negative arguments

	jal	zero, L22
L22_t:	jal	zero, L22_e
L22:	li	s0, 0xA5A5A5A5A5A5A5A5
	li	s1, 0xAA55AA55AA55AA55
	bltu	s0, s1, L22_t
	TEST_FAIL
L22_e:	
	
	# positive/negative arguments

	jal	zero, L23
L23_t:	jal	zero, L23_e
L23:	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0xA5A5A5A5A5A5A5A5
	bltu	s0, s1, L23_t
	TEST_FAIL
L23_e:	

	# zero/positive arguments

	jal	zero, L24
L24_t:	jal	zero, L24_e
L24:	li	s0, 0x0000000000000000
	li	s1, 0x5A5A5A5A5A5A5A5A
	bltu	s0, s1, L24_t
	TEST_FAIL
L24_e:	

	# zero/negative arguments

	jal	zero, L25
L25_t:	jal	zero, L25_e
L25:	li	s0, 0x0000000000000000
	li	s1, 0xA5A5A5A5A5A5A5A5
	bltu	s0, s1, L25_t
	TEST_FAIL
L25_e:	
	

	# ################################################################
	# Branch not taken, negative displacement

	# positive arguments

	jal	zero, L31
L31_t:
	TEST_FAIL
L31:	li	s0, 0x0A5A5A5A5A5A5A5A
	li	s1, 0x05A5A5A5A5A5A5A5
	bltu	s0, s1, L31_t

	# negative arguments

	jal	zero, L32
L32_t:
	TEST_FAIL
L32:	li	s0, 0xAA55AA55AA55AA55
	li	s1, 0xA5A5A5A5A5A5A5A5
	bltu	s0, s1, L32_t
	
	# negative/positive arguments
	
	jal	zero, L33
L33_t:
	TEST_FAIL
L33:	li	s0, 0xA5A5A5A5A5A5A5A5
	li	s1, 0x5A5A5A5A5A5A5A5A
	bltu	s0, s1, L33_t
	
	# positive/zero arguments

	jal	zero, L34
L34_t:
	TEST_FAIL
L34:	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0x0000000000000000
	bltu	s0, s1, L34_t
	
	# negative/zero arguments

	jal	zero, L35
L35_t:
	TEST_FAIL
L35:	li	s0, 0xA5A5A5A5A5A5A5A5
	li	s1, 0x0000000000000000
	bltu	s0, s1, L35_t
	
	# equal positive

	jal	zero, L36
L36_t:
	TEST_FAIL
L36:	li	s0, 0x5A5A5A5A5A5A5A5A
	li	s1, 0x5A5A5A5A5A5A5A5A
	bltu	s0, s1, L36_t
	
	# equal negative

	jal	zero, L37
L37_t:
	TEST_FAIL
L37:	li	s0, 0xA5A5A5A5A5A5A5A5
	li	s1, 0xA5A5A5A5A5A5A5A5
	bltu	s0, s1, L37_t
	
	# equal zero

	jal	zero, L38
L38_t:
	TEST_FAIL
L38:	li	s0, 0x0000000000000000
	li	s1, 0x0000000000000000
	bltu	s0, s1, L38_t
	

	TEST_END
	
