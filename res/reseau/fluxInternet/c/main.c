#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

unsigned short int download (char * url, char * fileName);

int main(int argc, char *argv[]) {
	char url [] = "http://www.google.fr/ig/api?weather=Paris", *fileName = "Paris.xml";
	//Download page "url" and save it to the file "fileName"
	download (url, fileName);
	
	/*
	//Read file and display to stdout
	FILE *file = fopen (fileName, "r");
	int c;
	while ((c = fgetc (file)) != EOF) putchar (c);
	*/

	return 0;
}

unsigned short int download (char * url, char * fileName) {
	FILE * file = NULL;
	CURL * session = NULL;    
	
	file = fopen(fileName, "w");
	
	if (file != NULL) { 
		//Create and init a new curl session
		session = curl_easy_init();
		curl_easy_setopt(session, CURLOPT_URL, url);
		
		curl_easy_setopt(session,  CURLOPT_WRITEDATA, file);
		curl_easy_setopt(session,  CURLOPT_WRITEFUNCTION, fwrite);
		
		//Download the page
		curl_easy_perform(session);
		
		//Close the file and the curl session
		fclose(file);
		curl_easy_cleanup(session);
	} else {
		printf("E: Le fichier de sauvegarde %s n'a pas pu être ouvert\n", fileName);
	}
}

