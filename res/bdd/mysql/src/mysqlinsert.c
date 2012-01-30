#include <mysql/mysql.h>
#include <stdio.h>
#include "mysqlinsert.h"

MYSQL* connectToMysql() {
	MYSQL* mysql = mysql_init(NULL);
	if(mysql) {
		puts("baaad");
	}

	if (mysql_real_connect(mysql,"localhost","hexanome","hexanome","pld",0,NULL,0)) {
		fprintf(stderr, "Error: failed to connect to database (%s)\n", mysql_error(mysql));
	} else {
		puts("connecté");
	}
	return mysql;
}

void closeMysql(MYSQL* mysql) {
	mysql_close(mysql);
}

void insertCapteur(MYSQL* mysql, int type, int numeroCapteur) {
	char s[64];
	sprintf(s, "insert into capteurs (type, numeroCapteur) values (%d, %d)", type, numeroCapteur);

	if(mysql_query(mysql, s)) {
		printf("Erreur: insert (%s)\n", mysql_error(mysql));
	} else {
		puts("okCapteur");
	}
}

void insertMesure(MYSQL* mysql, int idCapteur, int time, int typeMesure, double mesure) {
	char s[64];
	sprintf(s, "insert into mesure (idCapteur, time, typeMesure, mesure) values (%d, %d, %d, %f)",
		idCapteur, time, typeMesure, mesure);

	if(mysql_query(mysql, s)) {
				printf("Erreur: insert (%s)\n", mysql_error(mysql));
	} else {
		puts("okMesure");
	}
}

