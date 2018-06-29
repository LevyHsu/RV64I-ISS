	.text
	.align	2
	
	.globl	_start
_start:

	li	sp, 0x80000000
	li	s0, 0

	call	main

	jr	zero

