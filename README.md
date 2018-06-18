# RV64I-ISS
An instruction set simulator (ISS) for the RV64I subset of the RISC-V instruction set.

make
```bash
$make
```

parent directory
 - rv64sim
 - tests
      command_tests
      harness_tests
      instruction_tests
      compiled_tests

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

