# RV64I-ISS
An instruction set simulator (ISS) for the RV64I subset of the RISC-V instruction set.

make
```bash
$make
```

parent directory
 - rv64sim
 - tests<br/>
        command_tests<br/>
        harness_tests<br/>
        instruction_tests<br/>
        compiled_tests<br/>

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

