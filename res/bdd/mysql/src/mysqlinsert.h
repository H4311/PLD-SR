#ifndef MYSQL_INSERT
#define MYSQL_INSERT

#include <mysql/mysql.h>

// Types de capteurs
#define CAPTEUR_INOCEAN 0
#define CAPTEUR_SUNSPOT 1
#define CAPTEUR_RSS 2

MYSQL* connectToMysql();
void closeMysql(MYSQL* mysql);

void insertCapteur(MYSQL* mysql, int type, int numeroCapteur);

void insertMesure(MYSQL* mysql, int type, int numeroCapteur, long long time, int typeMesure, double mesure);

#endif
