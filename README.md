# RV64I-ISS
## An instruction set simulator (ISS) for the RV64I subset of the RISC-V instruction set with full memory simulation.

make
```bash
$make
```

parent directory
 - rv64sim
 - tests<br/>
        - command_tests<br/>
        - harness_tests<br/>
        - instruction_tests<br/>
        - compiled_tests<br/>
        - csr_tests<br/>
        
Debug with "-v" flag

command_tests
```bash
   $./rv64sim < command_test_m.cmd
```

instruction tests
```bash
   $./run_test instruction_test_add
```
or
```bash
   $./run_instruction_tests
```   

## Support instruction list:
### RV32I Base Instruction Set:
LUI AUIPC JAL JALR BEQ BNE BLT BGE BLTU BGEU LB LH LW LBU LHU SB SH SW ADDI SLTI SLTIU XORI ORI ANDI SLTI SLTIU XORI ORI ANDI SLLI SRLI SRAI ADD SUB SLL SLT SLTU XOR SRL SRA OR AND FENCE FENCE.I ECALL EBRAKE CSRRW CSRRS CSRRC CSRRWI CSRRSI CSRRCI
### RV64I Base Instruction Set (in addition to RV32I):
LWU LD SD SLLI SRLI SRAI ADDIW SLLIW SRLIW SRAIW ADDW SUBW SLLW SRLW SRAW
### CSR Register:
0xF11 Mevendorid\
0xF12 Marchid\
0xF13 Mimpid\
0xF14 Mhartid\
0x300 Mstatus\
0x301 Misa\
0x304 Mie\
0x305 Mtvec\
0x340 Mscratch\  
0x341 Mepc\
0x342 Mcause\
0x343 Mtval\
0x344 Mip\
