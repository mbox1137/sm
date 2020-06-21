.PHONY:	all clean
CC	= cc
#CC	= clang
ASM	= as
LD	= ld
EXEC	= main
OBJS	= main.o
LDFLAGS	= -O2 -Wall -Werror -std=gnu11 -lm
AFLAGS	=
CFLAGS	= -fverbose-asm -O3 -Wunused-variable -Werror=return-type -Werror=dangling-else -Werror=pointer-sign -Werror=unused-but-set-variable -Werror=maybe-uninitialized
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

