/*
 * test.cpp
 *
 *  Created on: 13 janv. 2012
 *      Author: bplanche
 */

#include "EnOceanReceptor.h"

void cb(enocean_data_structure in)
{
	char* hexstr = enocean_hexToHuman(in);
	printf("%s\n",hexstr);
	free(hexstr);
}

/**
 * main? Don't know, what main does ;)
 */
int main(int argc, char *argv[]) {
	enocean_data_structure mydata;
	printf("Testprogram started...\n");

	EnOceanReceptor recep = new EnOceanReceptor();
	recep.connect("134.214.105.28", 5000, cb);

	puts("waiting...");
	while (1==1) {
		// printhex(mydata);
	}
    printf("fertig!!!\n");
	return EXIT_SUCCESS;
}
