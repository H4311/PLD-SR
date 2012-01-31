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

void insertMesure(MYSQL* mysql, int idCapteur, int time, int typeMesure, double mesure) {
	char s[128];
	
	MYSQL_TIME  ts;
	MYSQL_BIND  bind[4];
	MYSQL_STMT  *stmt;
	
	stmt = mysql_stmt_init(mysql);

	sprintf(s, "INSERT INTO mesures (idCapteur, time, typeMesure, mesure) VALUES (?,?,?,?)");
	
	mysql_stmt_prepare(stmt, s, strlen(s));
	
	memset(bind, 0, sizeof(bind));

	bind[0].buffer_type= MYSQL_TYPE_LONG;
	bind[0].buffer= (char *)&idCapteur;
	bind[0].is_null= 0;
	bind[0].length= 0;
	
	bind[1].buffer_type= MYSQL_TYPE_TIMESTAMP;
	bind[1].buffer= (char *)&ts;
	bind[1].is_null= 0;
	bind[1].length= 0;
	
	bind[2].buffer_type= MYSQL_TYPE_LONG;
	bind[2].buffer= (char *)&typeMesure;
	bind[2].is_null= 0;
	bind[2].length= 0;
	
	bind[3].buffer_type= MYSQL_TYPE_DOUBLE;
	bind[3].buffer= (char *)&mesure;
	bind[3].is_null= 0;
	bind[3].length= 0;

	mysql_stmt_bind_param(stmt, bind);

	/* Fourni les données à envoyer dans la structure ts */
	ts.year= 2002;
	ts.month= 02;
	ts.day= 03;

	ts.hour= 10;
	ts.minute= 45;
	ts.second= 20;

	mysql_stmt_execute(stmt);
	
	mysql_stmt_close(stmt);
	
}

