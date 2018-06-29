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

SRCS=$(shell ls compiled_*.c)
HEXS=$(subst .c,.hex,$(SRCS))
DUMPS=$(subst .c,.dump,$(SRCS))

compiled_%.o: compiled_%.c
	$(CC) $(CFLAGS) -c -o $@ $<

start_compiled_%.o: start_compiled_%.s
	$(AS) $(ASFLAGS) -o $@ $<

compiled_%.elf: start_compiled_%.o compiled_%.o
	$(LD) $(LDFLAGS) -Ttext $(TEXT) -Tdata $(DATA) -o $@ $^

compiled_%.hex: compiled_%.elf
	$(OBJCOPY) --output-target ihex $< $@

compiled_%.dump: compiled_%.elf
	$(OBJDUMP) -d $< > $@

all: hex dump

hex: $(HEXS)

dump: $(DUMPS)

clean:
	$(RM) *.o *.elf *.hex *.dump
