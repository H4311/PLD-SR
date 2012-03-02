CXX := gcc
EXECUTABLE := main
 
all:
	$(CXX) test.c -o $(EXECUTABLE) -lmysqlclient_r -pthread
 
clean:
	rm -f $(EXECUTABLE) *.o
