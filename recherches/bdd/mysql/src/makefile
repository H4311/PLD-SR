CXX := gcc
EXECUTABLE := main
 
all:
	$(CXX) test.c mysqlinsert.c -ggdb -o $(EXECUTABLE) -lmysqlclient_r
 
clean:
	rm -f $(EXECUTABLE) *.o
