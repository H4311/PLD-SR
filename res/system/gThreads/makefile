CC = gcc
CFLAGS = -Wall -Werror -pedantic
EXE = gThread
INCLUDES = 
LIBS = 
OBJ_FILES = gThreads.o

all: $(EXE)

clean:
	rm $(EXE) $(OBJ_FILES)

$(EXE): $(OBJ_FILES)
	$(CC) -o $(EXE) $(OBJ_FILES) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
