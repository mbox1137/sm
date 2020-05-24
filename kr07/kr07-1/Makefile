.PHONY:	all clean
GDB	= -g
CC	= cc
#CC	= clang
ASM	= as
LD	= ld
EXEC	= main
OBJS	= main.o
#LDFLAGS	= -lm
LDFLAGS	= -no-pie -lm -m32 $(GDB)
AFLAGS	=
#CFLAGS	= -fverbose-asm -O3
CFLAGS	= -m32 -fverbose-asm -O3 $(GDB) -Wunused-variable -Werror=return-type -Werror=dangling-else
#-Os

ALL : $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c -o $@ $<
#	$(CC) $(CFLAGS) -S -o $<.S $<

%.o: %.S Makefile
	$(ASM) $(AFLAGS) -o $@ -a=$@.lst $<

clean:
	rm -f $(EXEC) *.o *.lst *.S *~

