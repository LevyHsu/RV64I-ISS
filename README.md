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
LUI AUIPC JAL JALR BEQ BNE BLT BGE BLTU BGEU LB LH LW LBU LHU SB SH SW ADDI SLTI SLTIU XORI ORI ANDI SLTI SLTIU XORI ORI ANDI SLLI SRLI SRAI ADD SUB SLL SLT SLTU XOR SRL SRA OR AND
### RV64I Base Instruction Set (in addition to RV32I): 
LWU LD SD SLLI SRLI SRAI ADDIW SLLIW SRLIW SRAIW ADDW SUBW SLLW SRLW SRAW
