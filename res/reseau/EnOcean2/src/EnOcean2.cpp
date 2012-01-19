/*
 * test.cpp
 *
 *  Created on: 13 janv. 2012
 *      Author: bplanche
 */

#include "EnOceanReceptor.h"
#include "EnOceanAnalyser.h"
#include <iostream>

/**
 * main? Don't know, what main does ;)
 */
int main(int argc, char *argv[]) {
	cout << "Testprogram started...\n";
	string adresse = "134.214.105.28";

	EnOceanReceptor recep = EnOceanReceptor();
	recep.open(adresse.c_str(), 5000);
	recep.read();

	cout << "Fin\n";

	return EXIT_SUCCESS;
}
