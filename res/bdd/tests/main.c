#include <stdio.h>
#include <sys/types.h>  
#include <unistd.h> 
#include "sqlite3.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for(i=0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

static void enOceanMesure(int numeroCapteur, double value) {
	
}

static void closeDB(sqlite3 *db) {
	sqlite3_close(db);
}

static int execCommand(sqlite3 *db, char* command) {
	char *zErrMsg = 0;
	int rc;
	rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s %s\n", zErrMsg, command);
		sqlite3_free(zErrMsg);
		return rc;
	}
	return 0;
}

static sqlite3 * openDB() {
	int rc;
	sqlite3 *db;
	rc = sqlite3_open("test.db", &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		closeDB(db);
		return NULL;
	}
	return db;
}


int main(int argc, char **argv){
	int i;
	sqlite3 *db;
	sqlite3 *db2;
	
	//sqlite3async_initialize(NULL, 0);
	
	pid_t pid1 = fork();
	if(pid1 == 0) {
		pid_t pid = fork();
		if(pid == 0) {
			db = openDB();
		
			for(i=0;i<200;i++) {
				execCommand(db, "SELECT * FROM capteurs;");
				usleep(20000);
			}
		
			closeDB(db);
		} else {
			db = openDB();
		
			execCommand(db, "PRAGMA synchronous = 0;");
			execCommand(db, "PRAGMA journal_mode = OFF;");
			for(i=0; i<500; i++) {
				execCommand(db, "INSERT INTO capteurs (type, numeroCapteur) VALUES (1, 1);");
				usleep(10000);
			}
		
			closeDB(db);
		}
		
		
	} else {
		//sqlite3async_run();
	}
	
	return 0;
}
