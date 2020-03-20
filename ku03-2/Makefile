.PHONY:	all clean

GDB	= -g

CC	= gcc
#CC	= clang
CFLAGS	= -m32 $(GDB)

ASM	= nasm
AFLAGS	= -f elf32 -g

AS	= as
ASFLAGS	= -c --32 $(GDB)
# -fPIC

LD	= $(CC)
LDFLAGS	= -no-pie -m32 -lm $(GDB)
#LDFLAGS	= -m elf_i386_fbsd	#-m32

EXEC	= main
OBJS	= main.o process.o

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
