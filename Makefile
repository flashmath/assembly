OBJ=kernel
CC=gcc -m32 -L/usr/lib32 -fno-pie -no-pie

all: $(OBJ)

kernel: kernel.o debug.o screen.o lib.o gdt.o
	ld --oformat binary -m elf_i386 -Ttext 1000 $^ -o $@

.o: .c
	$(CC) -c $^

clean:
	rm -f $(OBJ) *.o