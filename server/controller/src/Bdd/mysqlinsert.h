#ifndef MYSQL_INSERT
#define MYSQL_INSERT

#include <mysql/mysql.h>

// Types de capteurs
#define CAPTEUR_ENOCEAN 0
#define CAPTEUR_SUNSPOT 1
#define CAPTEUR_RSS 2

struct Result {
	int nbFields;
	int nbRows;
	int** tab;
};
typedef struct Result result;

MYSQL* connectToMysql();

void closeMysql(MYSQL* mysql);

void insertCapteur(MYSQL* mysql, int type, int numeroCapteur, int isGlobal, int idSujet);

//Fields renvoyés (dans l'ordre et tout en int) :
//type, numeroCapteur, isGlobal, idSujet
result* getCapteurs(MYSQL* mysql);


void insertMesure(MYSQL* mysql, int type, int numeroCapteur, long long time, int typeMesure, double mesure);

void insertActionneur(MYSQL* mysql, int num, int type);
void insertActionneurSujet(MYSQL* mysql, int nom, char* description, int isGlobal, int idSujet);
void insertPieces(MYSQL* mysql, char* nom, char* description);
void insertPatients(MYSQL* mysql, char* nom, int isMan, char* raisonHospitalisation, int idPiece);

#endif
