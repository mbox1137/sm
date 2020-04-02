.PHONY:	all clean
GDC	= -g
CC	= cc
#CC	= clang
ASM	= as
LD	= ld
EXEC	= main write_binary
OBJS	= write_binary.o main.o
LDFLAGS	= -lm -m32
AFLAGS	=
CFLAGS	= -fverbose-asm -m32 -O0
#-O3

ALL : $(EXEC)

#$(EXEC): $(OBJS)
#	$(CC) $(LDFLAGS) -o $@ $^

main : main.o
	$(CC) $(LDFLAGS) $(GDC) -o $@ $^

write_binary : write_binary.o
	$(CC) $(LDFLAGS) $(GDC) -o $@ $^

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(GDC) -c -o $@ $<

clean:
	rm -f $(EXEC) $(OBJS) *.lst *.S *~

