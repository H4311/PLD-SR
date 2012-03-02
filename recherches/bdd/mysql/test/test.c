#include <mysql/mysql.h>
#include <stdio.h>
#include <pthread.h>

#define THREAD_NB 4



/* Fonction pour les threads des clients. */
static void * doThread (void * p_data)
{
	unsigned int num_fields;
	unsigned int i;
	MYSQL_ROW row;
	MYSQL_RES *result;
	MYSQL mysql;
	
	int nb = (int) p_data;
	nb *= 100000;
	mysql_init(&mysql);

	if (!mysql_real_connect(&mysql,"localhost","hexanome","hexanome","pld",0,NULL,0)) {
		fprintf(stderr, "Failed to connect to database: Error: %s\n",
		mysql_error(&mysql));
	} else {
		char s[64];
		int l;
		for(l=nb;l<nb+10000;l++) {
			sprintf(s, "insert into capteurs (type, numeroCapteur) values (%d, %d)", l, l, l);
			if(mysql_query(&mysql, s)) {
				printf("Erreur : %s\n", mysql_error(&mysql));
			} else {
				result = mysql_store_result(&mysql);
				if(result) {
					num_fields = mysql_num_fields(result);
					while ((row = mysql_fetch_row(result))) {
						unsigned long *lengths;
						lengths = mysql_fetch_lengths(result);
						for(i = 0; i < num_fields; i++) {
							printf("[%.*s] \t", (int) lengths[i], row[i] ? row[i] : "NULL");
						}   
						printf("\n");
					}
				}
			}
			//usleep(10);
		}
		mysql_close(&mysql);
		int ret;
		pthread_exit(&ret);
	}

   return NULL;
}

int main(){
	int i;
	
	
	pthread_t threads[THREAD_NB];
	
	mysql_library_init(0, NULL, NULL);
	
	for(i=0; i<THREAD_NB; i++) {
		int t1 = pthread_create(&(threads [i]), NULL, doThread, (void *) i);
	}
	
	for(i=0; i<THREAD_NB; i++) {
		pthread_join(threads [i], NULL);
	}
	
	mysql_library_end();


	return 0;
	
}
