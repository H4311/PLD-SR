#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include "mysqlinsert.h"

MYSQL* connectToMysql() {
	MYSQL* mysql = mysql_init(NULL);
	if(mysql == NULL) {
		puts("Erreur de mysql_init");
	}

	if (!mysql_real_connect(mysql,"localhost","rithm","rithm","pld",0,NULL,0)) {
		fprintf(stderr, "Error: failed to connect to database (%s)\n", mysql_error(mysql));
	}
	return mysql;
}

void closeMysql(MYSQL* mysql) {
	mysql_close(mysql);
}

void insertCapteur(MYSQL* mysql, int type, int numeroCapteur, int isGlobal, int idSujet) {
	char s[512];
	sprintf(s, "INSERT INTO capteurs (type, numeroCapteur, isGlobal, idSujet) VALUES (%d, %d, %s, %d)",
			type, numeroCapteur, (isGlobal == 0 ? "false" : "true"), idSujet);

	if(mysql_query(mysql, s)) {
		printf("Erreur: insert (%s)\n", mysql_error(mysql));
	}
}

void insertMesure(MYSQL* mysql, int type, int numeroCapteur, long long time, int typeMesure, double mesure) {
	char s[512];
	sprintf(s, "INSERT INTO mesures (idCapteur, time, typeMesure, mesure) VALUES ((SELECT id FROM capteurs WHERE type=%d AND numeroCapteur=%d),%lld,%d,%f)", type, numeroCapteur, time, typeMesure, mesure);

	printf("<MYSQL>");
	printf("%s", s);
	printf("\n");
	if(mysql_query(mysql, s)) {
		printf("Erreur: insert (%s)\n", mysql_error(mysql));
	}
}

void insertActionneur(MYSQL* mysql, int num, int type) {
	char s[512];
	sprintf(s, "INSERT INTO actionneurs (numeroActionneur, type) VALUES (%d, %d)", num, type);

	if(mysql_query(mysql, s)) {
		printf("Erreur: insert (%s)\n", mysql_error(mysql));
	}
}

void insertActionneurSujet(MYSQL* mysql, int nom, char* description, int isGlobal, int idSujet) {
	char s[512];
	sprintf(s, "INSERT INTO actionneurSujet (nom, description, isGlobal, idSujet) VALUES ('%d', '%s', %s, %d)",
			nom, description, (isGlobal == 0 ? "false" : "true"), idSujet);

	if(mysql_query(mysql, s)) {
		printf("Erreur: insert (%s)\n", mysql_error(mysql));
	}
}

void insertPieces(MYSQL* mysql, char* nom, char* description) {
	char s[512];
	sprintf(s, "INSERT INTO pieces (nom, description) VALUES ('%s', '%s')", nom, description);

	if(mysql_query(mysql, s)) {
		printf("Erreur: insert (%s)\n", mysql_error(mysql));
	}
}

void insertPatients(MYSQL* mysql, char* nom, int isMan, char* raisonHospitalisation, int idPiece) {
	char s[512];
	sprintf(s, "INSERT INTO patients (nom, isMan, raisonHospitalisation, idPiece) VALUES ('%s', %s, '%s', %d)", nom, (isMan == 0 ? "false" : "true"), raisonHospitalisation, idPiece);

	if(mysql_query(mysql, s)) {
		printf("Erreur: insert (%s)\n", mysql_error(mysql));
	}
}
