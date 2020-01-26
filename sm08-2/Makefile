.PHONY:	all clean

CC	= gcc
CFLAGS	=
# -m32

ASM	= nasm
AFLAGS	= -f elf32 -g

AS	= as
ASFLAGS	= -c
# -fPIC

LD	= gcc
LDFLAGS	= -no-pie
#LDFLAGS	= -m elf_i386_fbsd	#-m32

EXEC	= abcd
OBJS	= abcd.o process.o
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
