#include <string.h>
#include "Meteo.h"

using namespace std;

int main(int argc, char *argv[]) {
	Meteo m;
	m.download(string("Paris"));
	m.parse(string("Paris"));
	return 0;
}

