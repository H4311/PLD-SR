# $Id: Makefile 95 2009-10-06 12:55:04Z simon_duquennoy $
#------------------------------------------------------------

CC = gcc
AR = ar
RANLIB = ranlib
CFLAGS = -Wall -pedantic -m32 -g

INSTALLDIR = ../libhw

OBJECTS = hw.o

HARDWARELIB = libhw.a

all: $(HARDWARELIB)

###------------------------------
### Bibliotheque
###------------------------------------------------------------
$(HARDWARELIB): $(OBJECTS)
	$(AR) cr $(HARDWARELIB) $(OBJECTS)
	$(RANLIB) $(HARDWARELIB)

###------------------------------
### Inclusions
###------------------------------------------------------------
Makefile.depends:
	$(CC) -MM *.c $(INCDIR) > Makefile.depends

include Makefile.depends

###------------------------------
### Tools
###------------------------------------------------------------
.PHONY: clean realclean 
clean:
	rm -f $(HARDWARELIB)
	rm -f *.o
	rm -f Makefile.depends

###------------------------------
### Install
###------------------------------------------------------------
.PHONY: install
install: $(HARDWARELIB)
	mkdir -p $(INSTALLDIR)/lib $(INSTALLDIR)/include
	install -m 644 $(HARDWARELIB) $(INSTALLDIR)/lib 
	install -m 644 hw.h $(INSTALLDIR)/include
