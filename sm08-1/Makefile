.PHONY:	all clean

CC	= gcc
CFLAGS	= -m32

ASM	= nasm
AFLAGS	= -f elf32 -g

AS	= gcc
ASFLAGS	= -m32 -c

LD	= gcc	#ld
LDFLAGS	= -m32	#-m elf_i386
#LDFLAGS	= -m elf_i386_fbsd	#-m32

EXEC	= aplusb
OBJS	= aplusb.o hw.o

ALL : $(EXEC)

hw : hw.o Makefile
	$(LD) $(LDFLAGS) -o hw hw.o

$(EXEC) : $(OBJS) Makefile
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.asm Makefile
	$(ASM) $(AFLAGS) -o $@ -l $@.lst $<

%.o: %.s Makefile
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	rm -f $(EXEC) $(OBJS) *~ *.lst .[^.]*~

all: $(EXEC)
