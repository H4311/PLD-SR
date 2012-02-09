#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mysqlinsert.h"

int main(){
	
	//Only one time in the program, to init the lib
	mysql_library_init(0, NULL, NULL);
	
	//For each thread :
	MYSQL* mysql = connectToMysql();
	
	insertCapteur(mysql, 1, 4, 5, 2, 3);
	time_t t;
	time(&t);
	insertMesure(mysql, 1, 4, t, 2, 5);
	insertActionneur(mysql, 10);
	insertActionneurSujet(mysql, "Action action !", "Ca agit..", 1, 10);
	insertPieces(mysql, "Chambre", "On dort ici");
	insertPatients(mysql, "Joe", 1, "Gelure des orteils", 2);
	
	closeMysql(mysql);
	
	//Only one time in the prog, to close the lib
	mysql_library_end();

	return 0;
	
}
