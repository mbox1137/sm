.PHONY:	all clean

GDB	= -g

CC	= gcc
CFLAGS	= -m32 -fverbose-asm -msse3
#CFLAGS	= -m32 -fverbose-asm -msse3 -nostdlib
# -std=c99

ASM	= nasm
AFLAGS	= -f elf32

AS	= as
ASFLAGS	= -c --32

LD	= gcc
LDFLAGS	= -no-pie -m32
#LD	= ld
#LDFLAGS	= -m elf_i386
#LDFLAGS	= -m elf_i386_fbsd	#-m32

EXEC	= main   binrev 5 test printData
OBJS	= main.o binrev.o marshall.o test.o printData.o
SCDRY	= main.s binrev.s marshall.s test.s printData.s

.SECONDARY: $(SCDRY)
ALL : $(EXEC)

main : main.o Makefile
	$(LD) $(LDFLAGS) -o main main.o

printData : printData.o Makefile
	$(LD) $(LDFLAGS) -o printData printData.o

test : test.o Makefile
	$(LD) $(LDFLAGS) -o test test.o

binrev : binrev.o marshall.o Makefile
	$(LD) $(LDFLAGS) -o binrev binrev.o marshall.o

5 : binrev
	cp binrev 5

#$(EXEC) : $(OBJS) Makefile
#	$(LD) $(LDFLAGS) $(GDB) -o $@ $(OBJS)

%.o: %.c
#	$(CC) $(CFLAGS) $(GDB) -c -o $@ $<

%.s: %.c Makefile *.h
	$(CC) $(CFLAGS) $(GDB) -S -o $@ $<

%.o: %.asm Makefile
	$(ASM) $(AFLAGS) $(GDB) -o $@ -l $@.lst $<

%.o: %.s Makefile
	$(AS) $(ASFLAGS) $(GDB) -a=$@.lst -o $@ $<

clean:
	rm -f $(EXEC) $(OBJS) $(SCDRY) *~ *.lst .[^.]*~ *.dat

