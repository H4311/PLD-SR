
main: sqlite3.o sqlite3async.o main.c
	gcc -o main main.c sqlite3.o sqlite3async.c -lpthread -ldl
	
sqlite3.o: sqlite3.c makefile
	gcc -c sqlite3.c -DSQLITE_THREADSAFE=1
#-DSQLITE_NO_SYNC


sqlite3async.o:
	gcc -c sqlite3async.c
