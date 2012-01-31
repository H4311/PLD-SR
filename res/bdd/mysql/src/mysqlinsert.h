#ifndef MYSQL_INSERT
#define MYSQL_INSERT

#include <mysql/mysql.h>

MYSQL* connectToMysql();
void closeMysql(MYSQL* mysql);

void insertCapteur(MYSQL* mysql, int type, int numeroCapteur);

void insertMesure(MYSQL* mysql, int idCapteur, int time, int typeMesure, double mesure);

#endif
