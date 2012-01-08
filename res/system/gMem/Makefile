CC      = gcc
CFLAGS  = -Wall -ansi -pedantic -g -m32

###------------------------------
### Main targets 
###------------------------------------------------------------
BINARIES = main
OBJECTS = gmem.o ctx.o

all: $(BINARIES)

###------------------------------
### Main rules 
###------------------------------------------------------------

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INCDIR)

%: %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

Makefile.depends:
	$(CC) -MM *.c $(INCDIR) > Makefile.depends

include Makefile.depends

main: main.o $(OBJECTS)


###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean
clean:
	$(RM) *.o $(BINARIES) Makefile.depends

