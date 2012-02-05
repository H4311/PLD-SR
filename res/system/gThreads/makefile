CC = gcc
CFLAGS = -Wall -pedantic #-Werror
EXE = gThread
INCLUDES = 
LIBS = 
OBJ_FILES = gThreads.o gContext.o appli.o

all: $(EXE)

clean:
	rm $(EXE) $(OBJ_FILES)

$(EXE): $(OBJ_FILES)
	$(CC) -o $(EXE) $(OBJ_FILES) $(LIBS) -m32 -ggdb

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
