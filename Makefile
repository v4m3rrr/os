C_SOURCES=$(wildcard kernel/src/*.c drivers/src/*.c)
C_OBJ_TEMP=${subst src,obj,$(C_SOURCES)}
C_OBJ=${C_OBJ_TEMP:.c=.o}

DIR=$(wildcard kernel drivers boot)

all: os-image
	qemu-system-i386 -drive format=raw,file=os-image
os-image: boot/obj/boot.bin kernel/obj/kernel.bin
	cat $^ > $@
boot/obj/boot.bin: boot/src/boot.asm
	nasm -f bin $^ -o $@
kernel/obj/kernel.bin: kernel/obj/kernel_entry.o $(C_OBJ)
	ld -e 0x0 -Ttext 0x1000 -m elf_i386 $^ -o $@ --oformat binary
kernel/obj/kernel_entry.o: kernel/src/kernel_entry.asm
	nasm -f elf32 $^ -o $@
kernel/obj/%.o: kernel/src/%.c
	gcc -c -fno-pie -ffreestanding -m32 -Ikernel/src -Idrivers/src -Iboot/src $^ -o $@
drivers/obj/%.o: drivers/src/%.c
	gcc -c -fno-pie -ffreestanding -m32 -Ikernel/src -Idrivers/src -Iboot/src $^ -o $@
	
