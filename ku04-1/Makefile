.PHONY:	all clean

GDB	= -g

CC	= gcc
CFLAGS	= -m32 -fverbose-asm -msse3
#CFLAGS	= -m32 -fverbose-asm -msse3 -nostdlib
# -std=c99

CPP	= g++

ASM	= nasm
AFLAGS	= -f elf32

AS	= as
ASFLAGS	= -c --32

LD	= $(CPP)
LDFLAGS	= -no-pie -m32
#LD	= ld
#LDFLAGS	= -m elf_i386
#LDFLAGS	= -m elf_i386_fbsd	#-m32

EXEC	= main
OBJS	= process.o main.o func.o
SCDRY	= process.s main.s

.SECONDARY: $(SCDRY)
ALL : $(EXEC)

main : main.o process.o func.o Makefile
	$(LD) $(LDFLAGS) -o main main.o process.o func.o

test : test.o Makefile
	$(LD) $(LDFLAGS) -o test test.o

#$(EXEC) : $(OBJS) Makefile
#	$(LD) $(LDFLAGS) $(GDB) -o $@ $(OBJS)

%.o: %.c
#	$(CC) $(CFLAGS) $(GDB) -c -o $@ $<

%.o: %.cpp
#	$(CC) $(CFLAGS) $(GDB) -c -o $@ $<

%.s: %.c Makefile *.h
	$(CC) $(CFLAGS) $(GDB) -S -o $@ $<

%.s: %.cpp Makefile *.h
	$(CPP) $(CFLAGS) $(GDB) -S -o $@ $<

%.o: %.asm Makefile
	$(ASM) $(AFLAGS) $(GDB) -o $@ -l $@.lst $<

%.o: %.s Makefile
	$(AS) $(ASFLAGS) $(GDB) -a=$@.lst -o $@ $<

clean:
	rm -f $(EXEC) $(OBJS) $(SCDRY) *~ *.lst .[^.]*~ *.dat

