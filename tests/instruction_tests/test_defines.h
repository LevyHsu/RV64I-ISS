	.macro  TEST_INIT
	addi	a0, zero, 0
	.endm

	.macro  TEST_EXPECT _r, _v
	li	a1, (\_v)
	bne	\_r, a1, _test_finish
	.endm

        .macro  TEST_FAIL
	addi	a0, zero, 0
	jr	zero
	.endm

	.macro  TEST_END
	addi	a0, zero, 1
_test_finish:
	jr	zero
	.endm

