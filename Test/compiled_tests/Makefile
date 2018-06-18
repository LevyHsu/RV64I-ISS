RM=rm -f
AS=riscv64-unknown-elf-as
CC=riscv64-unknown-elf-gcc
LD=riscv64-unknown-elf-ld
OBJCOPY=riscv64-unknown-elf-objcopy
OBJDUMP=riscv64-unknown-elf-objdump
RM=rm -f
ASFLAGS=-march=rv64i
CFLAGS=-march=rv64i -mabi=lp64
LDFLAGS=-m elf64lriscv
TEXT=0x00000000
DATA=0x00010000

SRCS=$(shell ls compiled_test_*.c)
CALL_SRCS=$(shell ls compiled_test_call_*.s)
OBJS=$(subst .c,.o,$(SRCS))
ELFS=$(subst .c,.elf,$(SRCS))
HEXS=$(subst .c,.hex,$(SRCS))
DUMPS=$(subst .c,.dump,$(SRCS))

compiled_test_%.o: compiled_test_%.c
	$(CC) $(CFLAGS) -c -o $@ $<

start.o: start.s
	$(AS) $(ASFLAGS) -o $@ $<

compiled_test_%.elf: start.o compiled_test_%.o
	$(LD) $(LDFLAGS) -Ttext $(TEXT) -Tdata $(DATA) -o $@ $^

compiled_test_%.hex: compiled_test_%.elf
	$(OBJCOPY) --output-target ihex $< $@

compiled_test_%.dump: compiled_test_%.elf
	$(OBJDUMP) -d $< > $@

all: hex dump

hex: $(HEXS)

dump: $(DUMPS)

clean:
	$(RM) $(OBJS) start.o $(ELFS) $(HEXS) $(DUMPS)
