.PHONY:	all clean

GDB	= -g

CC	= gcc
#clang
CFLAGS	= -m32 -fverbose-asm -Wunused-variable -Werror=return-type -Werror=dangling-else
#CFLAGS	= -m32 -fverbose-asm -msse3 -nostdlib
# -std=c99

CXX	= $(CC)

ASM	= nasm
AFLAGS	= -f elf32

AS	= as
ASFLAGS	= -c --32
#AS	= $(CC)
#ASFLAGS	= -m32 -c

LD	= $(CXX)
LDFLAGS	= -no-pie -m32 $(GDB)
#LD	= ld
#LDFLAGS	= -m elf_i386
#LDFLAGS	= -m elf_i386_fbsd	#-m32

EXEC	= client server
OBJS	= client.o server.o task.o
SCDRY	= client.s server.s task.s

.SECONDARY: $(SCDRY)
ALL : $(EXEC)

client : client.o Makefile
	$(LD) $(LDFLAGS) -o client client.o

server : server.o task.o Makefile
	$(LD) $(LDFLAGS) -o server server.o task.o

#$(EXEC) : $(OBJS) Makefile
#	$(LD) $(LDFLAGS) $(GDB) -o $@ $(OBJS)

%.o: %.c
#	$(CC) $(CFLAGS) $(GDB) -c -o $@ $<

%.o: %.cpp
#	$(CC) $(CFLAGS) $(GDB) -c -o $@ $<

%.s: %.c Makefile
	$(CC) $(CFLAGS) $(GDB) -S -o $@ $<

%.s: %.cpp Makefile
	$(CXX) $(CFLAGS) $(GDB) -S -o $@ $<

%.o: %.asm Makefile
	$(ASM) $(AFLAGS) $(GDB) -o $@ -l $@.lst $<

%.o: %.s Makefile
	$(AS) $(ASFLAGS) $(GDB) -a=$@.lst -o $@ $<

clean:
	rm -f $(EXEC) $(OBJS) $(SCDRY) *~ *.lst .[^.]*~ *.dat .[^.]*.bak *.bak *.log

