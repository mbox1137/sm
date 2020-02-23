.PHONY:	all clean

GDB	= -g

CC	= gcc
CFLAGS	= -m32 -fverbose-asm
# -std=c99

ASM	= nasm
AFLAGS	= -f elf32

AS	= as
ASFLAGS	= -c --32

LD	= gcc
LDFLAGS	= -no-pie -m32
#LDFLAGS	= -m elf_i386_fbsd	#-m32

EXEC	= main
OBJS	= main.o
SCDRY	= main.s

.SECONDARY: $(SCDRY)
ALL : $(EXEC)

hw : hw.o Makefile
	$(LD) $(LDFLAGS) -o hw hw.o

$(EXEC) : $(OBJS) Makefile
	$(LD) $(LDFLAGS) $(GDB) -o $@ $(OBJS)

%.o: %.c
#	$(CC) $(CFLAGS) $(GDB) -c -o $@ $<

%.s: %.c Makefile
	$(CC) $(CFLAGS) $(GDB) -S -o $@ $<

%.o: %.asm Makefile
	$(ASM) $(AFLAGS) $(GDB) -o $@ -l $@.lst $<

%.o: %.s Makefile
	$(AS) $(ASFLAGS) $(GDB) -a=$@.lst -o $@ $<

clean:
	rm -f $(EXEC) $(OBJS) $(SCDRY) *~ *.lst .[^.]*~

all: $(EXEC)
