.PHONY:	all clean

CC	= gcc
CFLAGS	= -m32 -lgcc

ASM	= nasm
AFLAGS	= -f elf32 -g

AS	= as
ASFLAGS	= -c --32
# -fPIC

LD	= gcc
LDFLAGS	= -no-pie -m32 -lm
#LDFLAGS	= -m elf_i386_fbsd	#-m32

EXEC	= main
OBJS	= main.o func.o

ALL : $(EXEC)

$(EXEC) : $(OBJS) Makefile
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c -o $@ $<
#	$(CC) $(CFLAGS) -S -o $@.s $<

#%.o: %.asm Makefile
#	$(ASM) $(AFLAGS) -o $@ -l $@.lst $<

%.o: %.s Makefile
	$(AS) $(ASFLAGS) -a=$@.lst -o $@ $<

clean:
	rm -f $(EXEC) $(OBJS) *~ *.lst .[^.]*~

all: $(EXEC)
