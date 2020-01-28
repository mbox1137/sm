.PHONY:	all clean

CC	= gcc
CFLAGS	=

ASM	= nasm
AFLAGS	= -f elf32 -g

AS	= as
ASFLAGS	= -c

LD	= ld
LDFLAGS	= -no-pie

EXEC	= tb abcd
OBJS	= process.o
EOBJS	= tb.o abcd.o

ALL : $(EXEC)

#%.o: %.c Makefile
#	$(CC) $(CFLAGS) -S -o $@.lst $<
#	$(CC) $(CFLAGS) -c -o $@ $<

%.s: %.c Makefile
	$(CC) $(CFLAGS) -S -o $@ $<

%.o: %.s abcd.inc Makefile
	$(AS) $(ASFLAGS) -a=$@.lst -o $@ $<

abcd : abcd.o $(OBJS) Makefile
	$(CC) $(LDFLAGS) -o $@ abcd.o $(OBJS)

tb : tb.o $(OBJS) Makefile
	$(CC) $(LDFLAGS) -o $@ tb.o $(OBJS)

%.o: %.asm Makefile
	$(ASM) $(AFLAGS) -o $@ -l $@.lst $<

clean:
	rm -f $(EXEC) $(EOBJS) $(OBJS) *~ *.lst .[^.]*~
