.PHONY:	all clean
CC	= cc
#CC	= clang
ASM	= as
LD	= ld
EXEC	= main
OBJS	= main.o
LDFLAGS	= -lm
AFLAGS	=
CFLAGS	= -lm -fverbose-asm -O3
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

