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
        j       interrupt_handler_machine_software_int

        .org    0x00000110
trap_vector_user_timer_int:
        j       interrupt_handler_user_timer_int

        .org    0x0000011c
trap_vector_machine_timer_int:
        j       interrupt_handler_machine_timer_int

        .org    0x00000120
trap_vector_user_external_int:
        j       interrupt_handler_user_external_int

        .org    0x0000012c
trap_vector_machine_external_int:
        j       interrupt_handler_machine_external_int

        .org    0x00000200
        
reset_vector:   
        .option push
        .option norelax
        la      gp, __global_pointer$   # Initialize gp
        .option pop
        li      sp, 0x00020000          # Initialize sp
        li      s0, 0                   # Initialize fp
        la      t0, trap_vector_exception
        ori     t0, t0, 1               # Vectored trap mode
        csrw    mtvec, t0
        li      t0, 0x999               # Set all mie bits
        csrw    mie, t0
        li      t0, 0x1800              # clear MPP (user mode)
        csrc    mstatus, t0
        li      t0, 0x80                # set MPIE
        csrs    mstatus, t0
        la      t0, 1f                  # Change to user mode, MIE enabled
        csrw    mepc, t0
        mret
1:      call    main
        j       trap_vector_reset

exception_handler:
        addi    sp, sp, -16
        sd      a0, 0(sp)       # save registers to be used in handler
        sd      a1, 8(sp)
        csrr    a0, mcause
        bltz    a0, interrupt_handler_user_software_int   # User software interrupt, same vector as exceptions
        slli    a0, a0, 2
        jr      %lo(exception_table)(a0)
        
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
        j       trap_vector_reset
        
exception_handler_store_addr_misaligned:
        j       trap_vector_reset
        
exception_handler_user_env_call:     
        j       trap_vector_reset

exception_handler_machine_env_call:     
        j       trap_vector_reset

interrupt_handler_user_software_int:
        la      a0, usi_count
        lw      a1, 0(a0)
        addi    a1, a1, 1
        sw      a1, 0(a0)
        ld      a0, 0(sp)
        ld      a1, 8(sp)
        addi    sp, sp, 16
        mret

interrupt_handler_machine_software_int: 
        addi    sp, sp, -16
        sd      a0, 0(sp)
        sd      a1, 8(sp)
        la      a0, msi_count
        lw      a1, 0(a0)
        addi    a1, a1, 1
        sw      a1, 0(a0)
        ld      a0, 0(sp)
        ld      a1, 8(sp)
        addi    sp, sp, 16
        mret

interrupt_handler_user_timer_int:
        addi    sp, sp, -16
        sd      a0, 0(sp)
        sd      a1, 8(sp)
        la      a0, uti_count
        lw      a1, 0(a0)
        addi    a1, a1, 1
        sw      a1, 0(a0)
        ld      a0, 0(sp)
        ld      a1, 8(sp)
        addi    sp, sp, 16
        mret

interrupt_handler_machine_timer_int:
        addi    sp, sp, -16
        sd      a0, 0(sp)
        sd      a1, 8(sp)
        la      a0, mti_count
        lw      a1, 0(a0)
        addi    a1, a1, 1
        sw      a1, 0(a0)
        ld      a0, 0(sp)
        ld      a1, 8(sp)
        addi    sp, sp, 16
        mret

interrupt_handler_user_external_int:
        addi    sp, sp, -16
        sd      a0, 0(sp)
        sd      a1, 8(sp)
        la      a0, uei_count
        lw      a1, 0(a0)
        addi    a1, a1, 1
        sw      a1, 0(a0)
        ld      a0, 0(sp)
        ld      a1, 8(sp)
        addi    sp, sp, 16
        mret

interrupt_handler_machine_external_int:
        addi    sp, sp, -16
        sd      a0, 0(sp)
        sd      a1, 8(sp)
        la      a0, mei_count
        lw      a1, 0(a0)
        addi    a1, a1, 1
        sw      a1, 0(a0)
        ld      a0, 0(sp)
        ld      a1, 8(sp)
        addi    sp, sp, 16
        mret


        .data
        .globl  usi_count
usi_count:      .word   0
        .globl  msi_count
msi_count:      .word   0
        .globl  uti_count
uti_count:      .word   0
        .globl  mti_count
mti_count:      .word   0
        .globl  uei_count
uei_count:      .word   0
        .globl  mei_count
mei_count:      .word   0
