ROOTDIR=../libhw
LIBNAME=hw
LIBFILE=$(ROOTDIR)/lib/lib$(LIBNAME).a

CC      = gcc
CFLAGS  = -Wall -pedantic -m32 #-ansi -g
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -l$(LIBNAME)

###------------------------------
### Main targets 
###------------------------------------------------------------
BINARIES= main

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

main: main.o ordonnancement.o $(LIBFILE)


###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean
clean:
	$(RM) *.o $(BINARIES) Makefile.depends

