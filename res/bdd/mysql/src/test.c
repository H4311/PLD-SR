#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include "mysqlinsert.h"

int main(){
	
	//Only one time in the program, to init the lib
	mysql_library_init(0, NULL, NULL);
	
	//For each thread :
	MYSQL* mysql = connectToMysql();
	
	insertCapteur(mysql, 1, 4);
	insertMesure(mysql, 4, 100, 2, 5);
	
	closeMysql(mysql);
	
	//Only one time in the prog, to close the lib
	mysql_library_end();

	return 0;
	
}
