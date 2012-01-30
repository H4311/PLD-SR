#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include "mysqlinsert.h"

int main(){
	
	//Only one time in the program, to init the lib
	mysql_library_init(0, NULL, NULL);
	
	//For each thread :
	puts("main");
	MYSQL* mysql = connectToMysql();
	
	puts("main");
	/*insertCapteur(mysql, 1, 4);
	puts("main");
	insertMesure(mysql, 4, 100, 2, 5);
	puts("main");
	
	closeMysql(mysql);
	puts("main");
	
	//Only one time in the prog, to close the lib
	mysql_library_end();

	*/
	return 0;
	
}
