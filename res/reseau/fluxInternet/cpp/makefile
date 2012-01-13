CC = g++
CFLAGS = -Wall -Werror -pedantic
EXEC_NAME = main
INCLUDES =
LIBS = -lcurl
OBJ_FILES = tinyxml.o tinyxmlparser.o tinyxmlerror.o tinystr.o main.o Meteo.o

all: $(EXEC_NAME)

clean:
	rm $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME): $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
