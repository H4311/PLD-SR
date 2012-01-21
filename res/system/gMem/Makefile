CC      = clang
CFLAGS  = -Wall -ansi -pedantic -g -m32 

###------------------------------
### Main targets 
###------------------------------------------------------------
BINARIES = main
OBJECTS = gmem.o 

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

main: $(OBJECTS) main.o 


###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean, rebuild
clean:
	$(RM) *.o $(BINARIES) Makefile.depends

rebuild: clean all
	

