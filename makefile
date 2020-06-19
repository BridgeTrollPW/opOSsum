#GCCPARAMS = -ffreestanding -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin
GCCPARAMS = -ffreestanding -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wall -std=c++11 -fstrength-reduce -fomit-frame-pointer -finline-functions -Iincludes
NASMPARAMS = -felf32

objects = sources/bootloader.o sources/kernel.o sources/io.o sources/gdt_flush.o sources/vga.o


%.o: %.cpp
	./i686-elf-5.2.0-Linux-x86_64/bin/i686-elf-g++ $(GCCPARAMS) -c $< -o $@ 

%.o: %.asm
	nasm -felf32 $< -o $@ 

opossum.bin: linker.ld $(objects)
	./i686-elf-5.2.0-Linux-x86_64/bin/i686-elf-ld -nostdlib -g -T linker.ld $(objects) -o opossum.bin 

opossum.iso: opossum.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp opossum.bin iso/boot/opossum.bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "opossum" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/opossum.bin'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=opossum.iso iso
	rm -rf iso

run: opossum.iso
	qemu-system-x86_64 -d int,pcall,unimp,guest_errors -cdrom opossum.iso

install: sonux.bin
	sudo cp $< /boot/opossum.bin

.PHONY: clean
clean:
	rm -f $(objects) opossum.bin opossum.iso *.o