.PHONY:	all clean

CC	= gcc
CFLAGS	= -m32

ASM	= nasm
AFLAGS	= -f elf32 -g

AS	= as
ASFLAGS	= -c --32
# -fPIC

LD	= gcc
LDFLAGS	= -no-pie -m32
#LDFLAGS	= -m elf_i386_fbsd	#-m32

EXEC	= main
OBJS	= main.o dotProduct.o
# hw.o

ALL : $(EXEC)

hw : hw.o Makefile
	$(LD) $(LDFLAGS) -o hw hw.o

$(EXEC) : $(OBJS) Makefile
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

#%.o: %.asm Makefile
#	$(ASM) $(AFLAGS) -o $@ -l $@.lst $<

%.o: %.s Makefile
	$(AS) $(ASFLAGS) -a=$@.lst -o $@ $<

clean:
	rm -f $(EXEC) $(OBJS) *~ *.lst .[^.]*~

all: $(EXEC)
