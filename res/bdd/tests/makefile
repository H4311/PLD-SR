
main: sqlite3.o sqlite3async.o main.c
	gcc -o main main.c sqlite3.o sqlite3async.c -lpthread -ldl
	
sqlite3.o: sqlite3.c
	gcc -c sqlite3.c 
#-DSQLITE_NO_SYNC
#-DSQLITE_THREADSAFE=2

sqlite3async.o:
	gcc -c sqlite3async.c
