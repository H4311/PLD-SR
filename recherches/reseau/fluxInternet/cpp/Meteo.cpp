#include "Meteo.h"
#include <cstdio>
#include <string>
#include "tinyxml.h"
#include <curl/curl.h>

using namespace std;

Meteo::Meteo() {

}

Meteo::~Meteo() {

}

void Meteo::download (string ville) {
	FILE * file = NULL;
	CURL * session = NULL; 
	
	file = fopen((ville + ".xml").c_str(), "w");
	
	if (file != NULL) { 
		//Create and init a new curl session
		session = curl_easy_init();
		curl_easy_setopt(session, CURLOPT_URL, ("http://www.google.fr/ig/api?weather=" + ville).c_str());
		
		curl_easy_setopt(session,  CURLOPT_WRITEDATA, file);
		curl_easy_setopt(session,  CURLOPT_WRITEFUNCTION, fwrite);
		
		//Download the page
		curl_easy_perform(session);
		
		//Close the file and the curl session
		fclose(file);
		curl_easy_cleanup(session);
	} else {
		printf("E: Le fichier de sauvegarde %s n'a pas pu être ouvert\n", ville.c_str());
	}
}

void Meteo::parse(string ville) {
	TiXmlDocument doc((ville + ".xml").c_str());
	bool loadOkay = doc.LoadFile();

	if(!loadOkay) {
		printf("Could not load test file 'Paris.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
		exit(1);
	}

	doc.Print(stdout);
	
	puts("####");
	
	TiXmlHandle hdl(&doc);
	TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().FirstChildElement().Element();
	
	
	printf("%s\n", elem->Value());
	TiXmlElement *next  = elem->NextSiblingElement();
	printf("%s\n", next->Value());
}
