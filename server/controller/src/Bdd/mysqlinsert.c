#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include "mysqlinsert.h"

MYSQL* connectToMysql() {
	MYSQL* mysql = mysql_init(NULL);
	if(mysql == NULL) {
		puts("Erreur de mysql_init");
	}

	if (!mysql_real_connect(mysql,"localhost","hexanome","hexanome","pld",0,NULL,0)) {
		fprintf(stderr, "Error: failed to connect to database (%s)\n", mysql_error(mysql));
	}
	return mysql;
}

void closeMysql(MYSQL* mysql) {
	mysql_close(mysql);
}

void insertCapteur(MYSQL* mysql, int type, int numeroCapteur) {
	char s[64];
	sprintf(s, "INSERT INTO capteurs (type, numeroCapteur) VALUES (%d, %d)", type, numeroCapteur);

	if(mysql_query(mysql, s)) {
		printf("Erreur: insert (%s)\n", mysql_error(mysql));
	}
}

void insertMesure(MYSQL* mysql, int type, int numeroCapteur, long long time, int typeMesure, double mesure) {
	char s[256];
	
	MYSQL_BIND  bind[3];
	MYSQL_STMT  *stmt;
	
	stmt = mysql_stmt_init(mysql);

	sprintf(s, "INSERT INTO mesures (idCapteur, time, typeMesure, mesure) VALUES ((SELECT id FROM capteurs WHERE type=%d AND numeroCapteur=%d),?,?,?)", type, numeroCapteur);
	
	mysql_stmt_prepare(stmt, s, strlen(s));
	
	memset(bind, 0, sizeof(bind));
	
	bind[0].buffer_type= FIELD_TYPE_LONGLONG;
	bind[0].buffer= (char *)&time;
	bind[0].is_null= 0;
	bind[0].length= 0;
	
	bind[1].buffer_type= MYSQL_TYPE_LONG;
	bind[1].buffer= (char *)&typeMesure;
	bind[1].is_null= 0;
	bind[1].length= 0;
	
	bind[2].buffer_type= MYSQL_TYPE_DOUBLE;
	bind[2].buffer= (char *)&mesure;
	bind[2].is_null= 0;
	bind[2].length= 0;

	mysql_stmt_bind_param(stmt, bind);

	mysql_stmt_execute(stmt);
	
	mysql_stmt_close(stmt);
	
}

