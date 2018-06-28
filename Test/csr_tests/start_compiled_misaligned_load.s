        .text
        
        .globl  _start

        .org    0x00000000
trap_vector_reset:      
        
_start:
        j       reset_vector

        .org    0x00000100
trap_vector_exception:
        j       exception_handler

        .org    0x0000010c
trap_vector_machine_software_int:
        j       trap_vector_reset

        .org    0x00000110
trap_vector_user_timer_int:
        j       trap_vector_reset

        .org    0x0000011c
trap_vector_machine_timer_int:
        j       trap_vector_reset

        .org    0x00000120
trap_vector_user_external_int:
        j       trap_vector_reset

        .org    0x0000012c
trap_vector_machine_external_int:
        j       trap_vector_reset

        .org    0x00000200
        
reset_vector:   
        la      t0, trap_vector_exception
        ori     t0, t0, 1               # Vectored trap mode
        csrw    mtvec, t0
        .option push
        .option norelax
        la      gp, __global_pointer$   # Initialize gp
        .option pop
        li      sp, 0x00020000          # Initialize sp
        li      s0, 0                   # Initialize fp
        call    main
        j       trap_vector_reset

exception_handler:
	addi	sp, sp, -24
	sd	t0, 0(sp)	# save registers to be used in handler
	sd	t1, 8(sp)
	sd	t2, 16(sp)
        csrr    t0, mcause
        bltz    t0, trap_vector_reset   # User software interrupt, same vector as exceptions
        slli    t0, t0, 2
        jr      %lo(exception_table)(t0)
        
exception_table:
        j       exception_handler_instr_addr_misaligned
        j       exception_handler_not_implemented        # instr_access_fault
        j       exception_handler_illegal_instr
        j       exception_handler_breakpoint
        j       exception_handler_load_addr_misaligned
        j       exception_handler_not_implemented       # load_access_fault
        j       exception_handler_store_addr_misaligned
        j       exception_handler_not_implemented       # store_access_fault
        j       exception_handler_user_env_call
        j       exception_handler_not_implemented       # supervisor_env_call
        j       exception_handler_not_implemented       # reserved
        j       exception_handler_machine_env_call

exception_handler_not_implemented:
        j       trap_vector_reset
        
exception_handler_instr_addr_misaligned:
        j       trap_vector_reset

exception_handler_illegal_instr:
        j       trap_vector_reset
        
exception_handler_breakpoint:
        j       trap_vector_reset
        
exception_handler_load_addr_misaligned:
        j       emulate_misaligned_ld
        
exception_handler_store_addr_misaligned:
        j       trap_vector_reset
        
exception_handler_user_env_call:     
        j       trap_vector_reset

exception_handler_machine_env_call:     
        j       trap_vector_reset


emulate_misaligned_ld:
#	csrr	t0, mtval	# misaligned address
	csrr	t0, 0x343	# mtval: misaligned address
	andi	t1, t0, -8      # round address down to aligned boundary
	addi	t2, t1, 8	# aligned address of next doubleword
	ld	t1, 0(t1)	# get first doubleword containing least significant bytes
	ld	t2, 0(t2)       # get second doubleword containing most significant bytes
	andi	t0, t0, 7	# byte offset from aligned boundary
	slli	t0, t0, 3	# bit offset from aligned boundary
	srl	t1, t1, t0	# shift ls bits down to bit 0, clearing ms bits
	addi	t0, t0, -64	# calculate 64 - bit offset = -(bit offset - 64)
	sub	t0, zero, t0
	sll	t2, t2, t0      # shift ms bits up to bit 63
	or	t2, t2, t1      # or to get final loaded value
	csrw	mscratch, t2	# stash in mscratch for now
	csrr	t0, mepc	# get address of load instruction
	lwu	t0, 0(t0)	# get load instruction word
	li	t1, 0xf80	# mask for rd
	and	t0, t0, t1	# t0 contains just rd number in bits 11:7
	la	t1, 2f		# get template csrr instruction
	lwu	t2, 0(t1)
	or	t2, t2, t0	# or in rd number
	la	t1, 1f	        # store edited instruction word just before mret
	sw	t2, 0(t1)
        csrr    t0, mepc	# increment mepc to point to next instruction
        addi    t0, t0, 4
        csrw    mepc, t0
	ld	t0, 0(sp)	# restore saved registers
	ld	t1, 8(sp)
	ld	t2, 16(sp)
	addi	sp, sp, 24
1:	nop			# to be replaced by edited csrr instruction
	mret
2:	csrr	x0, mscratch	# template instruction, x0 to be replaced with rd num
