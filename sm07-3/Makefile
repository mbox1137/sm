.PHONY:	all clean
#CC	= cc
CC	= clang
ASM	= as
LD	= ld
EXEC	= main
OBJS	= main.o bsearch2.o
LDFLAGS	= -lm
AFLAGS	=
CFLAGS	= -fverbose-asm -O3
# -std=gnu99
#-Os

ALL : $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c Makefile bsearch2.h
	$(CC) $(CFLAGS) -c -o $@ $<
#	$(CC) $(CFLAGS) -S -o $<.S $<

%.o: %.S Makefile
	$(ASM) $(AFLAGS) -o $@ -a=$@.lst $<

clean:
	rm -f $(EXEC) $(OBJS) *~ *.lst .[^.]*~

