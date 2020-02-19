.PHONY:	all clean

CC	= gcc
CFLAGS	= -m32 -fverbose-asm

ASM	= nasm
AFLAGS	= -f elf32 -g

AS	= as
ASFLAGS	= -c --32

LD	= gcc
LDFLAGS	= -no-pie -m32
#LDFLAGS	= -m elf_i386_fbsd	#-m32

EXEC	= main
OBJS	= main.o dotProduct.o
SCDRY	= main.s

.SECONDARY: $(SCDRY)
ALL : $(EXEC)

hw : hw.o Makefile
	$(LD) $(LDFLAGS) -o hw hw.o

$(EXEC) : $(OBJS) Makefile
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c
#	$(CC) $(CFLAGS) -c -o $@ $<

%.s: %.c Makefile
	$(CC) $(CFLAGS) -S -o $@ $<

%.o: %.asm Makefile
	$(ASM) $(AFLAGS) -o $@ -l $@.lst $<

%.o: %.s Makefile
	$(AS) $(ASFLAGS) -a=$@.lst -o $@ $<

clean:
	rm -f $(EXEC) $(OBJS) $(SCDRY) *~ *.lst .[^.]*~

all: $(EXEC)
