
main: sqlite3.o sqlite3async.o main.c
	gcc -o main main.c sqlite3.o sqlite3async.c -lpthread -ldl
	
sqlite3.o:
	gcc -c sqlite3.c

sqlite3async.o:
	gcc -c sqlite3async.c
