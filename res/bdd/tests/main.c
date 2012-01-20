#include <stdio.h>
#include <sys/types.h>  
#include <unistd.h> 
#include <sys/wait.h>
#include <stdlib.h>
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
		fprintf(stderr, "SQL error: %s %s %d\n", zErrMsg, command, rc);
		sqlite3_free(zErrMsg);
		return rc;
	}
	return 0;
}

static sqlite3 * openDB(int flags) {
	int rc;
	sqlite3 *db;
	rc = sqlite3_open_v2("test.db", &db, flags, NULL);
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
	
		
	pid_t pid = fork();
	if(pid == 0) {
		db = openDB(SQLITE_OPEN_READWRITE| SQLITE_OPEN_CREATE);
		sqlite3_busy_timeout(db, 1000);
	
		for(i=0;i<200;i++) {
			execCommand(db, "SELECT * FROM capteurs;");
			usleep(10000);
			//sleep(1);
		}
		puts("fin select");
		closeDB(db);
		exit(0);
	} else {
		db = openDB(SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
		sqlite3_busy_timeout(db, 1000);
	
		execCommand(db, "PRAGMA synchronous = 0;");
		char* sql = malloc(64);
		for(i=0; i<200; i++) {
			
			sprintf(sql, "INSERT INTO capteurs (type, numeroCapteur) VALUES (%d, 1);", i);
			execCommand(db, sql);
			usleep(10000);
		}
		free(sql);
		puts("fin insert");
	
		closeDB(db);
		int cpid, status;
	}
		
	
	return 0;
}
